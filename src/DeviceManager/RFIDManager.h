#ifndef RFIDMANAGER_H
#define RFIDMANAGER_H

#include "IRFIDManager.h"
#include "../Context.h"
#include "../Database/Controllers/Modules/DevicesController.h"
#include "../Database/Controllers/Modules/ModulesController.h"
#include "../Config/Device/DeviceConfigKeys.h"

class RFIDManager : public IRFIDManager {
private:
    Context* context;
    String resolveType(String type);
public:
    RFIDManager(Context* context);

    bool addRFID(String name, String chip_id, int pinNumber1, int pinNumber2, String type, int serverId) override;
    bool editRFID(int serverId, String name, String chip_id, int pinNumber1, int pinNumber2, String type) override;
    bool removeRFID(int serverId) override;
    RFIDFullEntity* getRFIDEntity(int serverId) override;
    std::vector<RFIDFullEntity*> getAllRFIDEntities() override;
};


RFIDManager::RFIDManager(Context* context): context(context) {}

String RFIDManager::resolveType(String type) {
    if (type == "RFID125Kh") {
        return ModuleTypes::RFID125KH;
    } else if (type == "RFIDPN532") {
        return ModuleTypes::RFIDPN532;
    } else {
        // Handle invalid type or default case
        return ModuleTypes::RFID125KH;
    }
}

bool RFIDManager::addRFID(String name, String chip_id, int pinNumber1, int pinNumber2, String type, int serverId) {
    DevicesController* devicesController = new DevicesController(context, storageType);
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        String moduleType = resolveType(type);
        ModuleEntity moduleEntity = ModuleEntity(name, moduleType, deviceEntity.id, serverId);
        int module_id = moduleController->Add(moduleEntity);
        if (serverId == 0) {
            moduleEntity.setServerId(module_id);
            moduleEntity.id = module_id;
            moduleEntity.setServerId(module_id);
            serverId = module_id;
            moduleController->Update(moduleEntity);
        }

        if (chip_id != context->getDeviceManager()->chipId) {
            String endpoint = String(context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE)) + "://" 
                + deviceEntity.GetValue(DevicesEntity::COLUMN_IP) 
                + "/rfidmanager/add";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number1\":\"" 
                + String(pinNumber1) + "\",\"pin_number2\":\"" + String(pinNumber2) + "\",\"type\":\"" + String(type) + "\",\"server_id\":\"" 
                + String(serverId) + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        RFIDEntity rfidEntity = RFIDEntity(module_id, pinNumber1, pinNumber2);
        RFIDController* rfidController = new RFIDController(context, storageType);
        rfidController->Add(rfidEntity);

        return true;
    }
    return false;
}

bool RFIDManager::editRFID(int serverId, String name, String chip_id, int pinNumber1, int pinNumber2, String type) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    DevicesController* devicesController = new DevicesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        String moduleType = resolveType(type);
        ModuleEntity moduleEntity = ModuleEntity(name, moduleType, deviceEntity.id, serverId);
        int module_id = moduleController->Add(moduleEntity);
        if (serverId == 0) {
            moduleEntity.setServerId(module_id);
            moduleEntity.id = module_id;
            moduleEntity.setServerId(module_id);
            serverId = module_id;
            moduleController->Update(moduleEntity);
        }

        if (chip_id != context->getDeviceManager()->chipId) {
            String endpoint = String(context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE)) + "://" 
                + deviceEntity.GetValue(DevicesEntity::COLUMN_IP) 
                + "/rfidmanager/edit";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number1\":\"" 
                + String(pinNumber1) + "\",\"pin_number2\":\"" + String(pinNumber2) + "\",\"type\":\"" + String(type) + "\",\"server_id\":\"" 
                + String(serverId) + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        RFIDEntity rfidEntity = RFIDEntity(module_id, pinNumber1, pinNumber2);
        RFIDController* rfidController = new RFIDController(context, storageType);
        rfidController->Update(rfidEntity);

        return true;
    }
    return false;
}

bool RFIDManager::removeRFID(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Delete(serverId)) {
        return true;
    }
    return false;
}

RFIDFullEntity* RFIDManager::getRFIDEntity(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getRFIDByServerId(serverId);
}

std::vector<RFIDFullEntity*> RFIDManager::getAllRFIDEntities() {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getAllRFIDs();
}


#endif // RFIDMANAGER_H
