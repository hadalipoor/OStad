#ifndef SOILMOISTURESENSORMANAGER_H
#define SOILMOISTURESENSORMANAGER_H

#include "ISoilMoistureSensorManager.h"
#include "../Context.h"
#include "../Database/Controllers/Modules/DevicesController.h"
#include "../Database/Controllers/Modules/ModulesController.h"
#include "../Config/Device/DeviceConfigKeys.h"

class SoilMoistureSensorManager : public ISoilMoistureSensorManager {
private:
    Context* context;
public:
    SoilMoistureSensorManager(Context* context);

    bool addSoilMoistureSensor(String name, String chip_id, int pinNumber, int dryThreshold, int wetThreshold, int serverId) override;
    bool editSoilMoistureSensor(int serverId, String name, String chip_id, int pinNumber, int dryThreshold, int wetThreshold) override;
    bool removeSoilMoistureSensor(int serverId) override;
    SoilMoistureFullEntity* getSoilMoistureSensorEntity(int serverId) override;
    std::vector<SoilMoistureFullEntity*> getAllSoilMoistureSensorEntities() override;
};

SoilMoistureSensorManager::SoilMoistureSensorManager(Context* context): context(context) {}

bool SoilMoistureSensorManager::addSoilMoistureSensor(String name, String chip_id, int pinNumber, int dryThreshold, int wetThreshold, int serverId) {
    DevicesController* devicesController = new DevicesController(context, storageType);
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::SOILMOISTURE, deviceEntity.id, serverId);
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
                + "/soilmoisturesensormanager/add";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number\":\""
                + String(pinNumber) + "\",\"dry_threshold\":\"" + String(dryThreshold) + "\",\"wet_threshold\":\"" 
                + String(wetThreshold) + "\",\"server_id\":\"" + String(serverId) + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        SoilMoistureEntity soilMoistureEntity = SoilMoistureEntity(module_id, pinNumber, dryThreshold, wetThreshold, ModuleTypes::SOILMOISTURE);
        SoilMoistureController* soilMoistureController = new SoilMoistureController(context, storageType);
        soilMoistureController->Add(soilMoistureEntity);

        return true;
    }
    return false;
}

bool SoilMoistureSensorManager::editSoilMoistureSensor(int serverId, String name, String chip_id, int pinNumber, int dryThreshold, int wetThreshold) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    DevicesController* devicesController = new DevicesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::SOILMOISTURE, deviceEntity.id, serverId);
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
                + "/soilmoisturesensormanager/edit";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number\":\""
                + String(pinNumber) + "\",\"dry_threshold\":\"" + String(dryThreshold) + "\",\"wet_threshold\":\"" 
                + String(wetThreshold) + "\",\"server_id\":\"" + String(serverId) + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        SoilMoistureEntity soilMoistureEntity = SoilMoistureEntity(module_id, pinNumber, dryThreshold, wetThreshold, ModuleTypes::SOILMOISTURE);
        SoilMoistureController* soilMoistureController = new SoilMoistureController(context, storageType);
        soilMoistureController->Update(soilMoistureEntity);

        return true;
    }
    return false;
}

bool SoilMoistureSensorManager::removeSoilMoistureSensor(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Delete(serverId)) {
        return true;
    }
    return false;
}

SoilMoistureFullEntity* SoilMoistureSensorManager::getSoilMoistureSensorEntity(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getSoilMoistureByServerId(serverId);
}

std::vector<SoilMoistureFullEntity*> SoilMoistureSensorManager::getAllSoilMoistureSensorEntities() {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getAllSoilMoistures();
}

#endif // SOILMOISTURESENSORMANAGER_H
