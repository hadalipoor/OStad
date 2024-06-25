#ifndef DHTSENSORMANAGER_H
#define DHTSENSORMANAGER_H

#include "IDHTSensorManager.h"
#include "../Context.h"
#include "../Database/Controllers/Modules/DevicesController.h"
#include "../Database/Controllers/Modules/ModulesController.h"
#include "Config/Device/DeviceConfigKeys.h"

class DHTSensorManager: public IDHTSensorManager {
private:
    Context* context;
public:
    DHTSensorManager(Context* context);

    bool addDHTSensor(String name, String chip_id, int pinNumber, String type, int serverId) override;
    bool editDHTSensor(int serverId, String name, String chip_id, int pinNumber, String type) override;
    bool removeDHTSensor(int serverId) override;
    DHTFullEntity* getDHTSensorEntity(int serverId) override;
    std::vector<DHTFullEntity*> getAllDHTSensorEntities() override;
};


DHTSensorManager::DHTSensorManager(Context* context): context(context) {}

bool DHTSensorManager::addDHTSensor(String name, String chip_id, int pinNumber, String type, int serverId) {
    DevicesController* devicesController = new DevicesController(context, storageType);
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::DHT, deviceEntity.id, serverId);
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
                + "/dhtsensormanager/add";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number\":\"" 
                + String(pinNumber) + "\",\"server_id\":\"" + String(serverId) + "\",\"type\":\"" + String(type) + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        DHTEntity dhtEntity = DHTEntity(module_id, type, pinNumber, 0,0,0,0);
        DHTController* dhtController = new DHTController(context, storageType);
        dhtController->Add(dhtEntity);

        return true;
    }
    return false;
}

bool DHTSensorManager::editDHTSensor(int serverId, String name, String chip_id, int pinNumber, String type) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    DevicesController* devicesController = new DevicesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::DHT, deviceEntity.id, serverId);
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
                + "/dhtsensormanager/edit";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number\":\"" 
                + String(pinNumber) + "\",\"server_id\":\"" + String(serverId) + "\",\"type\":\"" + String(type) + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        DHTEntity dhtEntity = DHTEntity(module_id, type, pinNumber,0,0,0,0);
        DHTController* dhtController = new DHTController(context, storageType);
        dhtController->Update(dhtEntity);

        return true;
    }
    return false;
}

bool DHTSensorManager::removeDHTSensor(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Delete(serverId)) {
        return true;
    }
    return false;
}

DHTFullEntity* DHTSensorManager::getDHTSensorEntity(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getDHTByServerId(serverId);
}

std::vector<DHTFullEntity*> DHTSensorManager::getAllDHTSensorEntities() {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getAllDHTs();
}

#endif // DHTSENSORMANAGER_H
