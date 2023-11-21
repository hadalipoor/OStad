#ifndef MODULESCONTROLLER_H
#define MODULESCONTROLLER_H

#include "../../Entities/Modules/ModuleEntity.h"
#include "../../Entities/Modules/ButtonFullEntity.h"
#include "../../Entities/Modules/ButtonEntity.h"
#include "ButtonController.h"

#include "../../Entities/Modules/RelayFullEntity.h"
#include "../../Entities/Modules/RelayEntity.h"
#include "RelayController.h"

#include "../../Entities/Modules/LCDFullEntity.h"
#include "../../Entities/Modules/LCDEntity.h"
#include "LCDController.h"

#include "../../Entities/Modules/DHTFullEntity.h"
#include "../../Entities/Modules/DHTEntity.h"
#include "DHTController.h"

#include "../../Entities/Modules/RGBFullEntity.h"
#include "../../Entities/Modules/RGBEntity.h"
#include "RGBController.h"

#include "../../Entities/Modules/PhotoresistorFullEntity.h"
#include "../../Entities/Modules/PhotoresistorEntity.h"
#include "PhotoresistorController.h"

#include "../../Entities/Modules/SoilMoistureFullEntity.h"
#include "../../Entities/Modules/SoilMoistureEntity.h"
#include "SoilMoistureController.h"

#include "../MainController.h"

class ModulesController : public MainController<ModuleEntity> {
    private:
        Context* context;
        ButtonController* buttonController;
    public:
        ModulesController(Context* context, StorageType _storageType);
        std::vector<ButtonFullEntity> getAllButtons();
        ButtonFullEntity getButtonByName(String name);
        int AddButton(ButtonFullEntity button);
        std::vector<RelayFullEntity> getAllRelays();
        int AddRelay(RelayFullEntity relay);
        std::vector<LCDFullEntity> getAllLCDs();
        int AddLCD(LCDFullEntity lcd);
        std::vector<DHTFullEntity> getAllDHTs();
        void AddDHT(DHTFullEntity dht);
        std::vector<RGBFullEntity> getAllRGBs();
        void AddRGB(RGBFullEntity rgb);
        std::vector<PhotoresistorFullEntity> getAllPhotoresistors();
        void AddPhotoresistor(PhotoresistorFullEntity photoresistor);
        std::vector<SoilMoistureFullEntity> getAllSoilMoistures();
        void AddSoilMoisture(SoilMoistureFullEntity soilMoisture);
};

ModulesController::ModulesController(Context* context, StorageType _storageType) : MainController<ModuleEntity>(context, "modules", _storageType), context(context) 
{

}

ButtonFullEntity ModulesController::getButtonByName(String name)
{
    buttonController = new ButtonController(context, _storageType);
    ButtonFullEntity fullButton;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
    _module.fromString(_module.toString());
        if (_module.GetValue(ModuleEntity::COLUMN_MODULE_TYPE) == ModuleTypes::BUTTON && _module.GetValue(ModuleEntity::COLUMN_NAME) == name)
        {
            ButtonEntity _button = buttonController->GetById(_module.id);
    _button.fromString(_button.toString());
            fullButton = ButtonFullEntity(_module.id, _button.id, _module.GetValue(ModuleEntity::COLUMN_NAME), _module.GetValue(ModuleEntity::COLUMN_MODULE_TYPE), _module.GetValue(ModuleEntity::COLUMN_CONNECTION_TYPE), _module.GetValue(ModuleEntity::COLUMN_NODE_ID).toInt(), 
            _module.GetValue(ModuleEntity::COLUMN_PIN_NUMBER).toInt(), _button.GetValue(ButtonEntity::COLUMN_BUTTON_TYPE), _button.GetValue(ButtonEntity::COLUMN_ACTIVE_HIGH).toInt(), _button.GetValue(ButtonEntity::COLUMN_PULLUP_ACTIVE).toInt(), _button.GetValue(ButtonEntity::COLUMN_DEBOUNCE_DELAY).toInt());
            // for (size_t j = 0; j < modules.size(); j++)
            // {
            //     modules[j].~ModuleEntity();
            // }
            modules.empty();
            return fullButton;
        }        
    }
    return fullButton;
}

std::vector<ButtonFullEntity> ModulesController::getAllButtons()
{
    buttonController = new ButtonController(context, _storageType);
    
    std::vector<ButtonFullEntity> buttons = std::vector<ButtonFullEntity>();
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
    _module.fromString(_module.toString());
        if (_module.GetValue(ModuleEntity::COLUMN_MODULE_TYPE) == ModuleTypes::BUTTON)
        {
            ButtonEntity _button = buttonController->GetById(_module.id);
            _button.fromString(_button.toString());
            ButtonFullEntity fullButton = ButtonFullEntity(_module.id, _button.id, _module.GetValue(ModuleEntity::COLUMN_NAME), _module.GetValue(ModuleEntity::COLUMN_MODULE_TYPE), _module.GetValue(ModuleEntity::COLUMN_CONNECTION_TYPE), _module.GetValue(ModuleEntity::COLUMN_NODE_ID).toInt(), 
            _module.GetValue(ModuleEntity::COLUMN_PIN_NUMBER).toInt(), _button.GetValue(ButtonEntity::COLUMN_BUTTON_TYPE), _button.GetValue(ButtonEntity::COLUMN_ACTIVE_HIGH).toInt(), _button.GetValue(ButtonEntity::COLUMN_PULLUP_ACTIVE).toInt(), _button.GetValue(ButtonEntity::COLUMN_DEBOUNCE_DELAY).toInt());
            buttons.push_back(fullButton);
        }        
    }
    
    for (size_t j = 0; j < modules.size(); j++)
    {
        // modules[j].~ModuleEntity();
    }
    
    // modules.empty();
    return buttons;
}

std::vector<RelayFullEntity> ModulesController::getAllRelays()
{
    RelayController relayController = RelayController(context, _storageType);
    std::vector<RelayFullEntity> relays;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module;
        _module.fromString(modules.at(i).toString());
        if (_module.GetValue(ModuleEntity::COLUMN_MODULE_TYPE) == ModuleTypes::RELAY)
        {
            RelayEntity _relay;
            _relay.fromString(relayController.Get(String(RelayEntity::COLUMN_MODULE_ID + "=" + _module.id)).at(0).toString());

            RelayFullEntity fullRelay = RelayFullEntity(_relay.id, _module.id, _module.GetValue(ModuleEntity::COLUMN_NAME), 
                _module.GetValue(ModuleEntity::COLUMN_MODULE_TYPE), _module.GetValue(ModuleEntity::COLUMN_CONNECTION_TYPE), 
                _module.GetValue(ModuleEntity::COLUMN_NODE_ID).toInt(), _module.GetValue(ModuleEntity::COLUMN_PIN_NUMBER).toInt(), 
                _relay.GetValue(RelayEntity::COLUMN_NORMALLY_OPEN).toInt());
            relays.push_back(fullRelay);
        }        
    }
    return relays;
}
std::vector<LCDFullEntity> ModulesController::getAllLCDs()
{
    LCDController lcdController = LCDController(context, _storageType);
    std::vector<LCDFullEntity> lcds;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
        if (_module.ModuleType == ModuleTypes::LCD)
        {
            LCDEntity _lcd = lcdController.GetById(_module.id);
            LCDFullEntity fullLcd = LCDFullEntity(_module.id, _lcd.id, _module.Name, _module.ModuleType, _module.ConnectionType, _module.NodeId, 
            _module.PinNumber, _lcd.Address, _lcd.Rows, _lcd.Cols, _lcd.Type);
            lcds.push_back(fullLcd);
        }        
    }
    return lcds;
}

std::vector<DHTFullEntity> ModulesController::getAllDHTs()
{
    DHTController dhtController = DHTController(context, _storageType);
    std::vector<DHTFullEntity> dhts;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
        if (_module.ModuleType == ModuleTypes::DHT)
        {
            DHTEntity _dht = dhtController.GetById(_module.id);
            DHTFullEntity fullDht = DHTFullEntity(_module.id, _dht.id, _module.Name, _module.ModuleType, _module.ConnectionType, _module.NodeId, 
            _module.PinNumber, _dht.Type, _dht.DryTreshold, _dht.WetTreshold, _dht.CoolTreshold, _dht.HotTreshold);
            dhts.push_back(fullDht);
        }        
    }
    return dhts;
}

std::vector<RGBFullEntity> ModulesController::getAllRGBs()
{
    RGBController rgbController = RGBController(context, _storageType);
    std::vector<RGBFullEntity> rgbs;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
        if (_module.ModuleType == ModuleTypes::RGB)
        {
            RGBEntity _rgb = rgbController.GetById(_module.id);
            RGBFullEntity fullRgb = RGBFullEntity(_module.id, _rgb.id, _module.Name, _module.ModuleType, _module.ConnectionType, _module.NodeId, 
            _module.PinNumber, _rgb.Type, _rgb.Rpin, _rgb.Gpin, _rgb.Bpin);
            rgbs.push_back(fullRgb);
        }        
    }
    return rgbs;
}

std::vector<PhotoresistorFullEntity> ModulesController::getAllPhotoresistors()
{
    PhotoresistorController photoresistorController = PhotoresistorController(context, _storageType);
    std::vector<PhotoresistorFullEntity> photoresistors;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
        if (_module.ModuleType == ModuleTypes::PHOTORESISTOR)
        {
            PhotoresistorEntity _photoresistor = photoresistorController.GetById(_module.id);
            PhotoresistorFullEntity fullPhotoresistor = PhotoresistorFullEntity(_module.id, _photoresistor.id, _module.Name, _module.ModuleType, _module.ConnectionType, _module.NodeId, 
            _module.PinNumber, _photoresistor.LowTreshold, _photoresistor.HighTreshold);
            photoresistors.push_back(fullPhotoresistor);
        }        
    }
    return photoresistors;
}

int ModulesController::AddButton(ButtonFullEntity button)
{
    ModuleEntity *_module = new ModuleEntity(button.ModuleId, button.Name, button.ModuleType,button.ConnectionType, button.NodeId, button.PinNumber);
    int _module_id = Add(*_module);
    ButtonEntity *_button = new ButtonEntity(_module_id, button.ButtonType, button.ActiveHigh, button.PullupActive, button.DebounceDelay);
    ButtonController *buttonController = new ButtonController(context, _storageType);
    return buttonController->Add(*_button);
}

int ModulesController::AddRelay(RelayFullEntity relay)
{
    ModuleEntity *_module = new ModuleEntity(relay.ModuleId, relay.Name, relay.ModuleType, relay.ConnectionType, relay.NodeId, relay.PinNumber);
    int _moduleId = Add(*_module);
    RelayEntity *_relay = new RelayEntity(_moduleId, relay.NormallyOpen);
    RelayController *relayController = new RelayController(context, _storageType);

    return relayController->Add(*_relay);
}

int ModulesController::AddLCD(LCDFullEntity lcd)
{
    ModuleEntity *_module = new ModuleEntity(lcd.ModuleId, lcd.Name, lcd.ModuleType, lcd.ConnectionType, lcd.NodeId, lcd.PinNumber);
    int _module_id = Add(*_module);
    LCDEntity *_lcd = new LCDEntity(_module_id, lcd.Address, lcd.Rows, lcd.Cols, lcd.Type);
    LCDController *lcdController = new LCDController(context, _storageType);

    return lcdController->Add(*_lcd);
}

void ModulesController::AddDHT(DHTFullEntity dht)
{
    ModuleEntity *_module = new ModuleEntity(dht.ModuleId, dht.Name, dht.ModuleType, dht.ConnectionType, dht.NodeId, dht.PinNumber);
    DHTEntity *_dht = new DHTEntity(dht.Type, dht.DryTreshold, dht.WetTreshold, dht.CoolTreshold, dht.HotTreshold);
    DHTController *dhtController = new DHTController(context, _storageType);

    dhtController->Add(*_dht);
    Add(*_module);
}

void ModulesController::AddRGB(RGBFullEntity rgb)
{
    ModuleEntity *_module = new ModuleEntity(rgb.ModuleId, rgb.Name, rgb.ModuleType, rgb.ConnectionType, rgb.NodeId, rgb.PinNumber);
    RGBEntity *_rgb = new RGBEntity(rgb.Type, rgb.Rpin, rgb.Gpin, rgb.Bpin);
    RGBController *rgbController = new RGBController(context, _storageType);

    rgbController->Add(*_rgb);
    Add(*_module);
}

void ModulesController::AddPhotoresistor(PhotoresistorFullEntity photoresistor)
{
    ModuleEntity *_module = new ModuleEntity(photoresistor.ModuleId, photoresistor.Name, photoresistor.ModuleType, photoresistor.ConnectionType, photoresistor.NodeId, photoresistor.PinNumber);
    PhotoresistorEntity *_photoresistor = new PhotoresistorEntity(photoresistor.LowTreshold, photoresistor.HighTreshold);
    PhotoresistorController *photoresistorController = new PhotoresistorController(context, _storageType);

    photoresistorController->Add(*_photoresistor);
    Add(*_module);
}

std::vector<SoilMoistureFullEntity> ModulesController::getAllSoilMoistures()
{
    SoilMoistureController soilMoistureController = SoilMoistureController(context, _storageType);
    std::vector<SoilMoistureFullEntity> soilMoistures;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
        if (_module.ModuleType == ModuleTypes::SOILMOISTURE)
        {
            SoilMoistureEntity _soilMoisture = soilMoistureController.GetById(_module.id);
            SoilMoistureFullEntity fullSoilMoisture = SoilMoistureFullEntity(_module.id, _soilMoisture.id, _module.Name, _module.ModuleType, _module.ConnectionType, _module.NodeId, 
            _module.PinNumber, _soilMoisture.DryTreshold, _soilMoisture.WetTreshold, _soilMoisture.Type);
            soilMoistures.push_back(fullSoilMoisture);
        }        
    }
    return soilMoistures;
}

void ModulesController::AddSoilMoisture(SoilMoistureFullEntity soilMoisture)
{
    ModuleEntity *_module = new ModuleEntity(soilMoisture.ModuleId, soilMoisture.Name, soilMoisture.ModuleType, soilMoisture.ConnectionType, soilMoisture.NodeId, soilMoisture.PinNumber);
    SoilMoistureEntity *_soilMoisture = new SoilMoistureEntity(0, soilMoisture.DryTreshold, soilMoisture.WetTreshold, soilMoisture.Type);
    SoilMoistureController *soilMoistureController = new SoilMoistureController(context, _storageType);

    soilMoistureController->Add(*_soilMoisture);
    Add(*_module);
}

#endif // MODULESCONTROLLER_H
