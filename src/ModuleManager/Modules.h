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
#include "../Database/Entities/Modules/RFIDEntity.h"
#include "../Database/Entities/Modules/RFIDFullEntity.h"

#include "Modules/Button.h"
#include "Modules/Relay.h"
#include "Modules/RFIDPN.h"
#include "Modules/DHTSensor.h"
#include "Modules/LCD16X2.h"
#include "Modules/OLEDLCD.h"
#include "Modules/RFID125Kh.h"
#include "Modules/SoilMoistureSensor.h"
// #include "Modules/"

#include "../Database/Controllers/Modules/ModulesController.h"

#include "../Context.h"

const static String NOT_FOUNDED = "notFounded";

class Modules: public IModules
{
private:
    Context* context;
    ModulesController *modulesController;

    std::vector<Button*> buttons;
    std::vector<Relay*> relays;
    std::vector<RFID125Kh*> rfid125khs;
    std::vector<RFIDPN532*> rfidnpn532s;
    std::vector<LCD16X2*> lcd16x2s;
    std::vector<OLEDLCD*> oledlcds;
    std::vector<SoilMoistureSensor*> soilMoistureSensors;
    std::vector<DHTSensor*> dhtSensors;

    ButtonFullEntity buttonFull;
    Button* _button;
    Button* emptyButton;
    SimCardManager* simCardManager;
    PCF8574* _pcf8574;

public:
    bool isNameUnique(String name);
    Modules(Context* context);

    IButton* getButton(int server_id) override;
    int addButton(IButton* button) override;
    IDHTSensor* getDHTSensor(int server_id) override;
    int addDHTSensor(IDHTSensor* dhtSensor) override;
    IRelay* getRelay(int server_id) override;
    int addRelay(IRelay* relay) override;
    IRFIDPN532* getRFIDPN532(int server_id) override;
    int addRFIDPN532(IRFIDPN532* rfid) override;
    IRFID125Kh* getRFID125Kh(int server_id) override;
    int addRFID125Kh(IRFID125Kh* rfid) override;
    ILCD16X2* getLCD16X2(int server_id) override;
    int addLCD16X2(ILCD16X2* lcd16x2) override;
    IOLEDLCD* getOLEDLCD(int server_id) override;
    int addOLEDLCD(IOLEDLCD* oledlcd) override;
    ISoilMoistureSensor* getSoilMoistureSensor(int server_id) override;
    int addSoilMoistureSensor(ISoilMoistureSensor* soilMoistureSensor) override;
    SimCardManager* getSimCardManager(int tx_pin, int rx_pin) override;
    void initialize() override;
    void update() override;
};

Modules::Modules(Context* cntx): context(cntx)
{

}

void Modules::initialize()
{
    modulesController = new ModulesController(context, storageType);
    
    // Load all relays from database to relays list
    std::vector<RelayFullEntity> relaysEntities = modulesController->getAllRelays();
    for(auto& relayEntity: relaysEntities)
    {
        relays.push_back(new Relay(context, relayEntity.ModuleId, relayEntity.ServerId, relayEntity.Name, relayEntity.DeviceId, relayEntity.PinNumber, relayEntity.NormallyOpen));
    }

    // Load all buttons from database to buttons list
    std::vector<ButtonFullEntity*> buttonEntities = modulesController->getAllButtons();
    for(auto& buttonEntity: buttonEntities)
    {
        buttons.push_back(new Button(context, buttonEntity->PinNumber, buttonEntity->Name, buttonEntity->ActiveHigh, buttonEntity->PullupActive));
    }

    // Load all RFID 125Khz and NPN532 modules from database to rfids list
    std::vector<RFIDFullEntity*> rfid125KhEntities = modulesController->getAllRFIDs();
    for(auto& rfidEntity: rfid125KhEntities)
    {
        if(rfidEntity->RFIDType == ModuleTypes::RFID125KH)
        {
            rfid125khs.push_back(new RFID125Kh(context, rfidEntity->PinNumber0, rfidEntity->PinNumber1, rfidEntity->ModuleId, rfidEntity->ServerId, rfidEntity->Name, ModuleTypes::RFID125KH, rfidEntity->DeviceId));
        }
        else
        {
            rfidnpn532s.push_back(new RFIDPN532(context, rfidEntity->PinNumber0, rfidEntity->ModuleId, rfidEntity->ServerId, rfidEntity->Name, ModuleTypes::RFIDPN532, rfidEntity->DeviceId));
        }
    }

    // Load all LCD16X2 from database to lcd16x2s list
    std::vector<LCDFullEntity*> lcd16x2Entities = modulesController->getAllLCDs();
    for(auto& lcdEntity: lcd16x2Entities)
    {
        if(lcdEntity->Type == "LCD16X2")
        {
            lcd16x2s.push_back(new LCD16X2(context, lcdEntity->ModuleId, lcdEntity->ServerId, lcdEntity->Name, lcdEntity->DeviceId, lcdEntity->Address, lcdEntity->Cols, lcdEntity->Rows));
        }
        else //lcdEntity->Type == "OLEDLCD"
        {
            oledlcds.push_back(new OLEDLCD(lcdEntity->ModuleId, lcdEntity->id, lcdEntity->Name, lcdEntity->Address, lcdEntity->Cols, lcdEntity->Rows, lcdEntity->DeviceId, lcdEntity->ServerId));
        }
    }

    // Load all soil moisture sensors from database to soilMoistureSensors list
    std::vector<SoilMoistureFullEntity*> soilMoistureEntities = modulesController->getAllSoilMoistures();
    for(auto& sensorEntity: soilMoistureEntities)
    {
        soilMoistureSensors.push_back(new SoilMoistureSensor(context, sensorEntity->PinNumber, sensorEntity->DryTreshold, sensorEntity->WetTreshold, sensorEntity->ModuleId, sensorEntity->ServerId, sensorEntity->Name, sensorEntity->ServerId));
    }

    // Load all DHT sensors from database to dhtSensors list
    std::vector<DHTFullEntity*> dhtEntities = modulesController->getAllDHTs();
    for(auto& dhtEntity: dhtEntities)
    {
        dhtSensors.push_back(new DHTSensor(context, dhtEntity->Name, dhtEntity->PinNumber, dhtEntity->Type, dhtEntity->ModuleId, dhtEntity->DeviceId, dhtEntity->ServerId));
    }

    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Modules Initialized.");
}

void Modules::update()
{
    for(auto& relay: relays)
    {
        relay->update();
    }
}

IButton* Modules::getButton(int server_id)
{
    for(auto& button: buttons)
    {
        if (button->getServerId() == server_id)
        {
            return button;
        }
    }
    return nullptr;
}

int Modules::addButton(IButton* button)
{
    if (!isNameUnique(button->getName()))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    ModuleEntity module_entity;
    if (button->getDeviceID() == -1)
    {
        module_entity = ModuleEntity(button->getName(), ModuleTypes::BUTTON, context->getDeviceManager()->deviceId, 0);
    }
    else
    {
        if(button->getServerId() == -1)
        {
            module_entity = ModuleEntity(button->getName(), ModuleTypes::BUTTON, button->getDeviceID(), 0);
        }
        else
        {
            module_entity = ModuleEntity(button->getName(), ModuleTypes::BUTTON, button->getDeviceID(), button->getServerId());
        }
    }
    
    int module_id = modulesController->Add(module_entity);
    if(button->getServerId() == -1)
    {
        module_entity.setServerId(module_id);
        modulesController->Update(module_entity);
    }
    ButtonController* buttonController = new ButtonController(context, storageType);
    ButtonEntity buttonEntity = ButtonEntity(module_id, "PIN", button->getPinNumber(), button->getActiveHigh(), button->getPullUpActive(), button->getDebounceDelay()); 
    int button_id = buttonController->Add(buttonEntity);

    // Cast IButton* to Button* and add to the buttons vector
    Button* btn = static_cast<Button*>(button);
    if (btn)
    {
        buttons.push_back(btn);
    }
    else
    {
        // Handle the error if the cast fails
        context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_NOT_ADDED_TO_DB, "Button cast failed: " + button->getName());
        return -1;
    }

    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "Button name : " + button->getName());
    return button_id;
}

IDHTSensor* Modules::getDHTSensor(int server_id)
{
    for(auto& sensor: dhtSensors)
    {
        if (sensor->getServerId() == server_id)
        {
            return sensor;
        }
    }
    return nullptr;
}

int Modules::addDHTSensor(IDHTSensor* dhtSensor)
{
    if (!isNameUnique(dhtSensor->getName()))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    ModuleEntity module_entity;
    if (dhtSensor->getDeviceID() == -1)
    {
        module_entity = ModuleEntity(dhtSensor->getName(), ModuleTypes::DHT, context->getDeviceManager()->deviceId, 0);
    }
    else
    {
        if(dhtSensor->getServerId() == -1)
        {
            module_entity = ModuleEntity(dhtSensor->getName(), ModuleTypes::DHT, dhtSensor->getDeviceID(), 0);
        }
        else
        {
            module_entity = ModuleEntity(dhtSensor->getName(), ModuleTypes::DHT, dhtSensor->getDeviceID(), dhtSensor->getServerId());
        }
    }
    
    int module_id = modulesController->Add(module_entity);
    if(dhtSensor->getServerId() == -1)
    {
        module_entity.setServerId(module_id);
        modulesController->Update(module_entity);
    }
    DHTController* dhtController = new DHTController(context, storageType);
    DHTEntity dhtEntity = DHTEntity(module_id, dhtSensor->getType(), dhtSensor->getPinNumber(), -1,-1,-1,-1); 
    int dht_id = dhtController->Add(dhtEntity);

    DHTSensor* dht = static_cast<DHTSensor*>(dhtSensor);
    if(dht)
    {
        dhtSensors.push_back(dht);
    }
    else
    {
        // Handle the error if the cast fails
        context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_NOT_ADDED_TO_DB, "DHT cast failed: " + dhtSensor->getName());
        return -1;
    }

    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "DHTSensor name : " + dhtSensor->getName());
    return dht_id;
}

IRelay* Modules::getRelay(int server_id)
{
    for(auto& relay: relays)
    {
        if (relay->getServerId() == server_id)
        {
            return relay;
        }
    }
    return nullptr;
}

int Modules::addRelay(IRelay* relay)
{
    if (!isNameUnique(relay->getName()))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    ModuleEntity module_entity;
    if (relay->getDeviceID() == -1)
    {
        module_entity = ModuleEntity(relay->getName(), ModuleTypes::RELAY, context->getDeviceManager()->deviceId, 0);
    }
    else
    {
        if(relay->getServerId() == -1)
        {
            module_entity = ModuleEntity(relay->getName(), ModuleTypes::RELAY, relay->getDeviceID(), 0);
        }
        else
        {
            module_entity = ModuleEntity(relay->getName(), ModuleTypes::RELAY, relay->getDeviceID(), relay->getServerId());
        }
    }
    
    int module_id = modulesController->Add(module_entity);
    if(relay->getServerId() == -1)
    {
        module_entity.setServerId(module_id);
        modulesController->Update(module_entity);
    }
    RelayController* relayController = new RelayController(context, storageType);
    RelayEntity relayEntity = RelayEntity(module_id, relay->getPinNumber(), relay->getNormallyOpen()); 
    int relay_id = relayController->Add(relayEntity);

    relays.push_back(static_cast<Relay*>(relay));

    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "Relay name : " + relay->getName());
    return relay_id;
}

IRFIDPN532* Modules::getRFIDPN532(int server_id)
{
    for(auto& rfid: rfidnpn532s)
    {
        if (rfid->getServerId() == server_id)
        {
            return rfid;
        }
    }
    return nullptr;
}

int Modules::addRFIDPN532(IRFIDPN532* rfid)
{
    if (!isNameUnique(rfid->getName()))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    ModuleEntity module_entity;
    if (rfid->getDeviceID() == -1)
    {
        module_entity = ModuleEntity(rfid->getName(), ModuleTypes::RFIDPN532, context->getDeviceManager()->deviceId, 0);
    }
    else
    {
        if(rfid->getServerId() == -1)
        {
            module_entity = ModuleEntity(rfid->getName(), ModuleTypes::RFIDPN532, rfid->getDeviceID(), 0);
        }
        else
        {
            module_entity = ModuleEntity(rfid->getName(), ModuleTypes::RFIDPN532, rfid->getDeviceID(), rfid->getServerId());
        }
    }
    
    int module_id = modulesController->Add(module_entity);
    if(rfid->getServerId() == -1)
    {
        module_entity.setServerId(module_id);
        modulesController->Update(module_entity);
    }
    RFIDPN532* rfidpn = static_cast<RFIDPN532*>(rfid);
    RFIDController* rfidController = new RFIDController(context, storageType);
    RFIDEntity rfidEntity = RFIDEntity(module_id, rfidpn->getSSPin(), -1); 
    int rfid_id = rfidController->Add(rfidEntity);

    if(rfidpn)
    {
        rfidnpn532s.push_back(rfidpn);
    }
    else
    {
        // Handle the error if the cast fails
        context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_NOT_ADDED_TO_DB, "RFID PN532 cast failed: " + rfidpn->getName());
        return -1;
    }


    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "RFIDPN532 name : " + rfid->getName());
    return rfid_id;
}

IRFID125Kh* Modules::getRFID125Kh(int server_id)
{
    for(auto& rfid: rfid125khs)
    {
        if (rfid->getServerId() == server_id)
        {
            return rfid;
        }
    }
    return nullptr;
}

int Modules::addRFID125Kh(IRFID125Kh* rfid)
{
    if (!isNameUnique(rfid->getName()))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    ModuleEntity module_entity;
    if (rfid->getDeviceID() == -1)
    {
        module_entity = ModuleEntity(rfid->getName(), ModuleTypes::RFID125KH, context->getDeviceManager()->deviceId, 0);
    }
    else
    {
        if(rfid->getServerId() == -1)
        {
            module_entity = ModuleEntity(rfid->getName(), ModuleTypes::RFID125KH, rfid->getDeviceID(), 0);
        }
        else
        {
            module_entity = ModuleEntity(rfid->getName(), ModuleTypes::RFID125KH, rfid->getDeviceID(), rfid->getServerId());
        }
    }
    
    int module_id = modulesController->Add(module_entity);
    if(rfid->getServerId() == -1)
    {
        module_entity.setServerId(module_id);
        modulesController->Update(module_entity);
    }
    RFIDController* rfidController = new RFIDController(context, storageType);
    RFID125Kh* rfid125 = static_cast<RFID125Kh*>(rfid);
    if(!rfid125)
    {
        // Handle the error if the cast fails
        context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_NOT_ADDED_TO_DB, "Button cast failed: " + rfid->getName());
        return -1;
    }

    RFIDEntity rfidEntity = RFIDEntity(module_id, rfid125->getPin0(), rfid125->getPin1()); 
    int rfid_id = rfidController->Add(rfidEntity);

    rfid125khs.push_back(rfid125);

    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "RFID125Kh name : " + rfid->getName());
    return rfid_id;
}

ILCD16X2* Modules::getLCD16X2(int server_id)
{
    for(auto& lcd: lcd16x2s)
    {
        if (lcd->getServerId() == server_id)
        {
            return lcd;
        }
    }
    return nullptr;
}

int Modules::addLCD16X2(ILCD16X2* lcd16x2)
{
    if (!isNameUnique(lcd16x2->getName()))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    ModuleEntity module_entity;
    if (lcd16x2->getDeviceID() == -1)
    {
        module_entity = ModuleEntity(lcd16x2->getName(), ModuleTypes::LCD, context->getDeviceManager()->deviceId, 0);
    }
    else
    {
        if(lcd16x2->getServerId() == -1)
        {
            module_entity = ModuleEntity(lcd16x2->getName(), ModuleTypes::LCD, lcd16x2->getDeviceID(), 0);
        }
        else
        {
            module_entity = ModuleEntity(lcd16x2->getName(), ModuleTypes::LCD, lcd16x2->getDeviceID(), lcd16x2->getServerId());
        }
    }
    
    int module_id = modulesController->Add(module_entity);
    if(lcd16x2->getServerId() == -1)
    {
        module_entity.setServerId(module_id);
        modulesController->Update(module_entity);
    }
    LCDController* lcdController = new LCDController(context, storageType);
    LCDEntity lcdEntity = LCDEntity(module_id, -1, lcd16x2->getWidth(), lcd16x2->getHeight(), "LCD16X2"); 
    int lcd_id = lcdController->Add(lcdEntity);

    LCD16X2* lcd = static_cast<LCD16X2*>(lcd16x2);
    if(lcd)
    {
        lcd16x2s.push_back(lcd);
    }
    else
    {
        // Handle the error if the cast fails
        context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_NOT_ADDED_TO_DB, "LCD 16X2 cast failed: " + lcd16x2->getName());
        return -1;
    }


    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "LCD16X2 name : " + lcd16x2->getName());
    return lcd_id;
}

IOLEDLCD* Modules::getOLEDLCD(int server_id)
{
    for(auto& oled: oledlcds)
    {
        if (oled->getServerId() == server_id)
        {
            return oled;
        }
    }
    return nullptr;
}

int Modules::addOLEDLCD(IOLEDLCD* oledlcd)
{
    if (!isNameUnique(oledlcd->getName()))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    ModuleEntity module_entity;
    if (oledlcd->getDeviceID() == -1)
    {
        module_entity = ModuleEntity(oledlcd->getName(), ModuleTypes::LCD, context->getDeviceManager()->deviceId, 0);
    }
    else
    {
        if(oledlcd->getServerId() == -1)
        {
            module_entity = ModuleEntity(oledlcd->getName(), ModuleTypes::LCD, oledlcd->getDeviceID(), 0);
        }
        else
        {
            module_entity = ModuleEntity(oledlcd->getName(), ModuleTypes::LCD, oledlcd->getDeviceID(), oledlcd->getServerId());
        }
    }
    
    int module_id = modulesController->Add(module_entity);
    if(oledlcd->getServerId() == -1)
    {
        module_entity.setServerId(module_id);
        modulesController->Update(module_entity);
    }
    LCDController* lcdController = new LCDController(context, storageType);
    LCDEntity lcdEntity = LCDEntity(module_id, oledlcd->getAddress(), oledlcd->getCol(), oledlcd->getRows(), "OLED"); 
    int lcd_id = lcdController->Add(lcdEntity);

    OLEDLCD* oled = static_cast<OLEDLCD*>(oledlcd);
    if(oled)
    {
        oledlcds.push_back(oled);
    }
    else
    {
        // Handle the error if the cast fails
        context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_NOT_ADDED_TO_DB, "OLED LCD cast failed: " + oledlcd->getName());
        return -1;
    }


    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "OLEDLCD name : " + oledlcd->getName());
    return lcd_id;
}

ISoilMoistureSensor* Modules::getSoilMoistureSensor(int server_id)
{
    for(auto& sensor: soilMoistureSensors)
    {
        if (sensor->getServerId() == server_id)
        {
            return sensor;
        }
    }
    return nullptr;
}

int Modules::addSoilMoistureSensor(ISoilMoistureSensor* soilMoistureSensor)
{
    if (!isNameUnique(soilMoistureSensor->getName()))
    {
        return -1;
    }
    modulesController = new ModulesController(context, storageType);
    ModuleEntity module_entity;
    if (soilMoistureSensor->getDeviceID() == -1)
    {
        module_entity = ModuleEntity(soilMoistureSensor->getName(), ModuleTypes::SOILMOISTURE, context->getDeviceManager()->deviceId, 0);
    }
    else
    {
        if(soilMoistureSensor->getServerId() == -1)
        {
            module_entity = ModuleEntity(soilMoistureSensor->getName(), ModuleTypes::SOILMOISTURE, soilMoistureSensor->getDeviceID(), 0);
        }
        else
        {
            module_entity = ModuleEntity(soilMoistureSensor->getName(), ModuleTypes::SOILMOISTURE, soilMoistureSensor->getDeviceID(), soilMoistureSensor->getServerId());
        }
    }
    
    int module_id = modulesController->Add(module_entity);
    if(soilMoistureSensor->getServerId() == -1)
    {
        module_entity.setServerId(module_id);
        modulesController->Update(module_entity);
    }
    SoilMoistureController* soilMoistureController = new SoilMoistureController(context, storageType);
    SoilMoistureEntity soilMoistureEntity = SoilMoistureEntity(module_id, soilMoistureSensor->getSensorPin(), soilMoistureSensor->getDryThreshold(), soilMoistureSensor->getWetThreshold(), ""); 
    int soilMoisture_id = soilMoistureController->Add(soilMoistureEntity);

    SoilMoistureSensor* soilMoisture = static_cast<SoilMoistureSensor*>(soilMoistureSensor);
    if(soilMoisture)
    {
        soilMoistureSensors.push_back(soilMoisture);
    }
    else
    {
        // Handle the error if the cast fails
        context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::MODULE_NOT_ADDED_TO_DB, "SoilMoisture Sensor cast failed: " + soilMoistureSensor->getName());
        return -1;
    }


    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::MODULE_ADDED_TO_DB, "SoilMoistureSensor name : " + soilMoistureSensor->getName());
    return soilMoisture_id;
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
