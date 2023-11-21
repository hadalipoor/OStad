// Modules.h

#ifndef MODULESS_H
#define MODULESS_H

#include "IModules.h"

#include "../Database/Entities/Modules/ButtonFullEntity.h"
#include "../Database/Entities/Modules/RelayFullEntity.h"
#include "../Database/Entities/Modules/DHTFullEntity.h"
#include "../Database/Entities/Modules/LCDFullEntity.h"
#include "../Database/Entities/Modules/PhotoresistorFullEntity.h"
#include "../Database/Entities/Modules/RGBFullEntity.h"
#include "../Database/Entities/Modules/SoilMoistureFullEntity.h"

#include "../Database/Controllers/Modules/ModulesController.h"

#include "../Context.h"

const static String NOT_FOUNDED = "notFounded";

class Modules: public IModules
{
private:
    Context* context;
    ModulesController *modulesController;

    std::vector<RelayFullEntity> relays;
    std::vector<LCDFullEntity> lcd16x2s;
    std::vector<LCDFullEntity> oledlcds;
    std::vector<SoilMoistureFullEntity> sensors;

    ButtonFullEntity buttonFull;
    Button* _button;
    Button* emptyButton;
    SimCardManager* simCardManager;
    PCF8574* _pcf8574;

public:
    bool isNameUnique(String name);
    Modules(Context* context);

    Button* getButton(String name) override;
    Button* getButton(String name, PCF8574* pcf8574) override;
    int addButton(Button* button) override;
    Relay* getRelay(String name) override;
    int addRelay(Relay* relay) override;
    LCD16X2* getLCD16X2(String name) override;
    int addLCD16X2(LCD16X2* lcd16x2) override;
    OLEDLCD* getOLEDLCD(String name) override;
    void addOLEDLCD(OLEDLCD* oledlcd) override;
    SoilMoistureSensor* getSoilMoistureSensor(String name) override;
    void addSoilMoistureSensor(SoilMoistureSensor* soilMoistureSensor) override;
    SimCardManager* getSimCardManager(int tx_pin, int rx_pin) override;
    void initialize() override;
};

Modules::Modules(Context* cntx): context(cntx)
{

}

void Modules::initialize()
{
    modulesController = new ModulesController(context, storageType);
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Modules Initialized.");
}

Button* Modules::getButton(String name)
{
    Button* button;
    buttonFull = modulesController->getButtonByName(name);
    button = new Button(buttonFull.PinNumber, name, buttonFull.ActiveHigh, buttonFull.PullupActive, buttonFull.ButtonType);
    button->setDebounceDelay(buttonFull.DebounceDelay);
    // button->setLongPressTime(buttonFull.)
    return  button;
}

Button* Modules::getButton(String name, PCF8574* pcf8574)
{
    Button* button;
    buttonFull = modulesController->getButtonByName(name);
    if (buttonFull.ButtonType == "PCF8574")
    {
        button = new Button(buttonFull.PinNumber, name, buttonFull.ActiveHigh, buttonFull.PullupActive, Button::getButtonType(buttonFull.ButtonType), pcf8574);        
    }
    else if(buttonFull.ButtonType == "PIN")
    {
        button = new Button(buttonFull.PinNumber, name, buttonFull.ActiveHigh, buttonFull.PullupActive, buttonFull.ButtonType);
    }
    button->setDebounceDelay(buttonFull.DebounceDelay);
    // button->setLongPressTime(buttonFull.)
    return button;
}

int Modules::addButton(Button* button)
{
    ButtonFullEntity *buttonEntity = button->getEntity();
    if (!isNameUnique(buttonEntity->Name))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    int button_id = modulesController->AddButton(*buttonEntity);
    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "Button name : " + buttonEntity->Name);
    return button_id;
}

Relay* Modules::getRelay(String name)
{
    relays = modulesController->getAllRelays();
    for (size_t i = 0; i < relays.size(); i++)
    {
        RelayFullEntity relay = relays.at(i);
        if (relay.Name == name)
        {
            return new Relay(relay.PinNumber, name, relay.NormallyOpen); 
        }        
    }
    context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_NOT_FOUND_IN_DB, "Relay name : " + name);
    return new Relay(-1, NOT_FOUNDED, true); // Empty Relay
}

int32_t Modules::addRelay(Relay* relay)
{
    RelayFullEntity *relayEntity = relay->getEntity();
    if (!isNameUnique(relayEntity->Name))
    {
        return -1;
    }

    int _id = modulesController->AddRelay(*relayEntity);
    if(_id == -1)
    {
        context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "Relay name : " + relayEntity->Name);
    }
    else{
        context->getLogger()->log(LogLevel::INFO_LEVEL,LogTitles::MODULE_NOT_ADDED_TO_DB, "Relay name : " + relayEntity->Name);
    }
    return _id;
}

// Continuing from previous code ...

LCD16X2* Modules::getLCD16X2(String name)
{
    lcd16x2s = modulesController->getAllLCDs();
    for (size_t i = 0; i < lcd16x2s.size(); i++)
    {
        LCDFullEntity oled = lcd16x2s.at(i);
        if (oled.Name == name)
        {
            return new LCD16X2(name, oled.Address, oled.Cols, oled.Rows); 
        }        
    }
    context->getLogger()->log(LogLevel::ERROR_LEVEL,LogTitles::MODULE_NOT_FOUND_IN_DB, "LCD16X2 name : " + name);
    return new LCD16X2(NOT_FOUNDED, -1, 0, 0); // Empty LCD16X2
}

int Modules::addLCD16X2(LCD16X2* oledlcd)
{
    LCDFullEntity *oledEntity = oledlcd->getEntity();
    if (!isNameUnique(oledEntity->Name))
    {
        return -1;
    }
    int _id = modulesController->AddLCD(*oledEntity);
    if(_id == -1)
    {
        context->getLogger()->log(LogLevel::ERROR_LEVEL,LogTitles::MODULE_NOT_ADDED_TO_DB, "LCD16X2 name : " + oledEntity->Name);
    }
    else{
        context->getLogger()->log(LogLevel::INFO_LEVEL,LogTitles::MODULE_ADDED_TO_DB, "LCD16X2 name : " + oledEntity->Name);
    }
    return _id;
}

OLEDLCD* Modules::getOLEDLCD(String name)
{
    oledlcds = modulesController->getAllLCDs();
    for (size_t i = 0; i < oledlcds.size(); i++)
    {
        LCDFullEntity lcd = oledlcds.at(i);
        if (lcd.Name == name)
        {
            return new OLEDLCD(name, lcd.Address, lcd.Cols, lcd.Rows); 
        }        
    }
    context->getLogger()->log(LogLevel::ERROR_LEVEL,LogTitles::MODULE_NOT_FOUND_IN_DB, "LCDHandler name : " + name);
    return new OLEDLCD(NOT_FOUNDED, -1, 0, 0); // Empty LCDHandler
}

void Modules::addOLEDLCD(OLEDLCD* lcdHandler)
{
    LCDFullEntity *lcdEntity = lcdHandler->getEntity();
    if (!isNameUnique(lcdEntity->Name))
    {
        return;
    }
    modulesController->AddLCD(*lcdEntity);
    context->getLogger()->log(LogLevel::INFO_LEVEL,LogTitles::MODULE_ADDED_TO_DB, "LCDHandler name : " + lcdEntity->Name);
}

SoilMoistureSensor* Modules::getSoilMoistureSensor(String name)
{
    sensors = modulesController->getAllSoilMoistures();
    for (size_t i = 0; i < sensors.size(); i++)
    {
        SoilMoistureFullEntity sensor = sensors.at(i);
        if (sensor.Name == name)
        {
            return new SoilMoistureSensor(name, sensor.ConnectionType, sensor.NodeId, sensor.PinNumber, sensor.DryTreshold, sensor.WetTreshold); 
        }        
    }
    context->getLogger()->log(LogLevel::ERROR_LEVEL,LogTitles::MODULE_NOT_FOUND_IN_DB, "SoilMoistureSensor name : " + name);
    return new SoilMoistureSensor( NOT_FOUNDED,"" , -1, -1, 0, 0); // Empty SoilMoistureSensor
}

void Modules::addSoilMoistureSensor(SoilMoistureSensor* soilMoistureSensor)
{
    SoilMoistureFullEntity *sensorEntity = soilMoistureSensor->getEntity();
    if (!isNameUnique(sensorEntity->Name))
    {
        return;
    }
    modulesController->AddSoilMoisture(*sensorEntity);
    context->getLogger()->log(LogLevel::INFO_LEVEL,LogTitles::MODULE_ADDED_TO_DB, "SoilMoistureSensor name : " + sensorEntity->Name);
}

SimCardManager* Modules::getSimCardManager(int tx_pin, int rx_pin)
{
    return simCardManager;
}

bool Modules::isNameUnique(String name)
{
    std::vector<ModuleEntity> modules = modulesController->Get(String(ModuleEntity::COLUMN_NAME + "=" + name));
    if (modules.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }    
}

#endif
