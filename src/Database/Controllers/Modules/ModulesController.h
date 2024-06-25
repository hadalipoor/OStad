#ifndef MODULESCONTROLLER_H
#define MODULESCONTROLLER_H

#include "../../Entities/Modules/ModuleEntity.h"
#include "../../Entities/Modules/ButtonFullEntity.h"
#include "../../Entities/Modules/ButtonEntity.h"
#include "ButtonController.h"

#include "../../Entities/Modules/RelayFullEntity.h"
#include "../../Entities/Modules/RelayEntity.h"
#include "RelayController.h"

#include "../../Entities/Modules/RFIDFullEntity.h"
#include "../../Entities/Modules/RFIDEntity.h"
#include "RFIDController.h"

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
    //TODO: finish all getByServerId functions 
        ModulesController(Context* context, StorageType _storageType);

        std::vector<ButtonFullEntity*> getAllButtons();
        ButtonFullEntity* getButtonById(int serverId);

        std::vector<RelayFullEntity> getAllRelays();
        RelayFullEntity getRelayByServerId(int serverId);

        std::vector<RFIDFullEntity*> getAllRFIDs();
        RFIDFullEntity* getRFIDByServerId(int server_id);

        std::vector<LCDFullEntity*> getAllLCDs();
        LCDFullEntity* getLCDByServerId(int server_id);

        std::vector<DHTFullEntity*> getAllDHTs();
        DHTFullEntity* getDHTByServerId(int serverId);
        
        std::vector<RGBFullEntity> getAllRGBs();
        RGBFullEntity getRGBByServerId(int server_id);

        std::vector<PhotoresistorFullEntity> getAllPhotoresistors();
        PhotoresistorFullEntity getPhotoresistorByServerId(int server_id);

        std::vector<SoilMoistureFullEntity*> getAllSoilMoistures();
        SoilMoistureFullEntity* getSoilMoistureByServerId(int server_id);
};

ModulesController::ModulesController(Context* context, StorageType _storageType) : MainController<ModuleEntity>(context, "modules", _storageType), context(context) 
{

}

ButtonFullEntity* ModulesController::getButtonById(int serverId)
{
    std::vector<ButtonFullEntity*> fullButtons = getAllButtons();
    for (auto& button: fullButtons)
    {
        if(button->ServerId == serverId)
        {
            return button;
        }        
    }
    return new ButtonFullEntity();
}

std::vector<ButtonFullEntity*> ModulesController::getAllButtons()
{
    buttonController = new ButtonController(context, _storageType);
    
    std::vector<ButtonFullEntity*> buttons = std::vector<ButtonFullEntity*>();
    std::vector<ModuleEntity> modules = GetAll();
    for (auto& _module :modules)
    {
        
    _module.fromString(_module.toString());
        if (_module.getModuleType() == ModuleTypes::BUTTON)
        {
            ButtonEntity _button = buttonController->GetById(_module.id);
            _button.fromString(_button.toString());
            ButtonFullEntity* fullButton = new ButtonFullEntity(_button.id, _module.id, _module.getName(), 
            _button.getPinNumber(), _button.getButtonType(), _button.getActiveHigh(), _button.getPullupActive(), _button.getDebounceDelay(), _module.getDeviceId(), _module.getServerId());
            buttons.push_back(fullButton);
        }        
    }
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
        if (_module.getModuleType() == ModuleTypes::RELAY)
        {
            RelayEntity _relay;
            std::vector<RelayEntity> _relayEntities = relayController.Get(String(RelayEntity::COLUMN_MODULEID + "=" + _module.id));
            if(_relayEntities.size() > 0)
            {
                _relay.fromString(_relayEntities.at(0).toString());
            }
            else
            {
                return relays;
            }

            RelayFullEntity fullRelay = RelayFullEntity(_relay.id, _module.id, _module.GetValue(ModuleEntity::COLUMN_NAME), 
                _module.getModuleType(),
                _module.getDeviceId(), _relay.getPinNumber(), 
                _relay.getNormallyOpen(), _module.getServerId());
            relays.push_back(fullRelay);
        }        
    }
    return relays;
}

RelayFullEntity ModulesController::getRelayByServerId(int serverId)
{
    std::vector<RelayFullEntity> relays = getAllRelays();
    for(auto& relay: relays)
    {
        if (relay.ServerId == serverId)
        {
            return relay;
        }
    }

    return RelayFullEntity();
}

std::vector<RFIDFullEntity*> ModulesController::getAllRFIDs()
{
    RFIDController rfidController = RFIDController(context, _storageType);
    std::vector<RFIDFullEntity*> rfids;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module;
        _module.fromString(modules.at(i).toString());
        if (_module.getModuleType() == ModuleTypes::RFIDPN532 || _module.getModuleType() == ModuleTypes::RFID125KH)
        {
            RFIDEntity _rfid;
            _rfid.fromString(rfidController.Get(String(RFIDEntity::COLUMN_MODULEID + "=" + _module.id)).at(0).toString());

            RFIDFullEntity* fullRFID = new RFIDFullEntity(_rfid.id, _module.id, _module.getName(), 
                _rfid.getPinNumber1(), _rfid.getPinNumber2(), _module.getDeviceId(), _module.getServerId());
            rfids.push_back(fullRFID);
        }        
    }
    return rfids;
}

RFIDFullEntity* ModulesController::getRFIDByServerId(int server_id)
{
    std::vector<RFIDFullEntity*> rfids = getAllRFIDs();
    for (auto& rfid: rfids)
    {
        if (rfid->ServerId == server_id)
        {
            return rfid;
        }
    }
    return new RFIDFullEntity();
}

std::vector<LCDFullEntity*> ModulesController::getAllLCDs()
{
    LCDController lcdController = LCDController(context, _storageType);
    std::vector<LCDFullEntity*> lcds;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
        if (_module.getModuleType() == ModuleTypes::LCD)
        {
            LCDEntity _lcd = lcdController.GetById(_module.id);
            LCDFullEntity* fullLcd = new LCDFullEntity(_module.id, _lcd.id, _module.getName(),
            _lcd.getAddress(), _lcd.getRows(), _lcd.getCols(), _lcd.getType(), _module.getDeviceId(), _module.getServerId());
            lcds.push_back(fullLcd);
        }        
    }
    return lcds;
}

LCDFullEntity* ModulesController::getLCDByServerId(int server_id)
{
    std::vector<LCDFullEntity*> lcds = getAllLCDs();
    for(auto& lcd: lcds)
    {
        if (lcd->ServerId == server_id)
        {
            return lcd;
        }
    }
    return new LCDFullEntity();
}

DHTFullEntity* ModulesController::getDHTByServerId(int server_id)
{
    std::vector<DHTFullEntity*> dhts = getAllDHTs();
    for(auto& dhtSensor: dhts)
    {
        Serial.println(dhtSensor->ServerId);
        Serial.println(server_id);

        if (dhtSensor->ServerId == server_id)
        {
            return dhtSensor;
        }
    }

    return new DHTFullEntity();
}

std::vector<DHTFullEntity*> ModulesController::getAllDHTs()
{
    DHTController dhtController = DHTController(context, _storageType);
    std::vector<DHTFullEntity*> dhts;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module;
        _module.fromString(modules.at(i).toString());
        if (_module.getModuleType() == ModuleTypes::DHT)
        {
            DHTEntity _dht;
            std::vector<DHTEntity> _dhtEntities = dhtController.Get(String(DHTEntity::COLUMN_MODULEID + "=" + _module.id));
            if(_dhtEntities.size() > 0)
            {
                _dht.fromString(_dhtEntities.at(0).toString());
            }
            else
            {
                return dhts;
            }

            DHTFullEntity* fullDHT = new DHTFullEntity(_dht.id, _module.id, _module.getName(), _dht.getPinNumber(),
                _dht.getType(), _dht.getDryTreshold(), _dht.getWetTreshold(), _dht.getCoolTreshold(), _dht.getHotTreshold(),
                _module.getDeviceId(), _module.getServerId());
            dhts.push_back(fullDHT);
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
        if (_module.getModuleType() == ModuleTypes::RGB)
        {
            RGBEntity _rgb = rgbController.GetById(_module.id);
            RGBFullEntity fullRgb = RGBFullEntity(_module.id, _rgb.id, _module.getName(),
            _rgb.getPinNumber(), _rgb.getType(), _rgb.getRpin(), _rgb.getGpin(), _rgb.getBpin(), _module.getDeviceId(), _module.getServerId());
            rgbs.push_back(fullRgb);
        }        
    }
    return rgbs;
}

RGBFullEntity ModulesController::getRGBByServerId(int server_id)
{
    std::vector<RGBFullEntity> rgbs = getAllRGBs();
    for(auto& rgb: rgbs)
    {
        if (rgb.ServerId == server_id)
        {
            return rgb;
        }
    }
    return RGBFullEntity();
}

std::vector<PhotoresistorFullEntity> ModulesController::getAllPhotoresistors()
{
    PhotoresistorController photoresistorController = PhotoresistorController(context, _storageType);
    std::vector<PhotoresistorFullEntity> photoresistors;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
        if (_module.getModuleType() == ModuleTypes::PHOTORESISTOR)
        {
            PhotoresistorEntity _photoresistor = photoresistorController.GetById(_module.id);
            PhotoresistorFullEntity fullPhotoresistor = PhotoresistorFullEntity(_module.id, _photoresistor.id, _module.getName(), _photoresistor.getPinNumber(),
                    _photoresistor.getLowTreshold(), _photoresistor.getHighTreshold(), _module.getDeviceId(), _module. getServerId());
            photoresistors.push_back(fullPhotoresistor);
        }        
    }
    return photoresistors;
}

PhotoresistorFullEntity ModulesController::getPhotoresistorByServerId(int server_id)
{
    std::vector<PhotoresistorFullEntity> photoresistors = getAllPhotoresistors();
    for(auto& photoresistor: photoresistors)
    {
        if (photoresistor.ServerId == server_id)
        {
            return photoresistor;
        }
    }
    
    return PhotoresistorFullEntity();
}

std::vector<SoilMoistureFullEntity*> ModulesController::getAllSoilMoistures()
{
    SoilMoistureController soilMoistureController = SoilMoistureController(context, _storageType);
    std::vector<SoilMoistureFullEntity*> soilMoistures;
    std::vector<ModuleEntity> modules = GetAll();
    for (size_t i = 0; i < modules.size(); i++)
    {
        ModuleEntity _module = modules.at(i);
        if (_module.getModuleType() == ModuleTypes::SOILMOISTURE)
        {
            SoilMoistureEntity _soilMoisture = soilMoistureController.GetById(_module.id);
            SoilMoistureFullEntity* fullSoilMoisture = new SoilMoistureFullEntity(_module.id, _soilMoisture.id, _module.getName(),
            _soilMoisture.getPinNumber(), _soilMoisture.getDryTreshold(), _soilMoisture.getWetTreshold(), _soilMoisture.getType(), _module.getDeviceId(), _module.getServerId());
            soilMoistures.push_back(fullSoilMoisture);
        }        
    }
    return soilMoistures;
}

SoilMoistureFullEntity* ModulesController::getSoilMoistureByServerId(int server_id)
{
    std::vector<SoilMoistureFullEntity*> soilMoistures = getAllSoilMoistures();
    for(auto& soilMoisture: soilMoistures)
    {
        if (soilMoisture->ServerId == server_id)
        {
            return soilMoisture;
        }
    }
    
    return new SoilMoistureFullEntity();
}
#endif // MODULESCONTROLLER_H
