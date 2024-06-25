#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include "ILCDManager.h"
#include "../Context.h"
#include "../Database/Controllers/Modules/DevicesController.h"
#include "../Database/Controllers/Modules/ModulesController.h"
#include "../Config/Device/DeviceConfigKeys.h"

class LCDManager : public ILCDManager {
private:
    Context* context;
public:
    LCDManager(Context* context);

    bool addLCD(String name, String chip_id, int address, int rows, int cols, String type, int serverId) override;
    bool editLCD(int serverId, String name, String chip_id, int address, int rows, int cols, String type) override;
    bool removeLCD(int serverId) override;
    LCDFullEntity* getLCDEntity(int serverId) override;
    std::vector<LCDFullEntity*> getAllLCDEntities() override;
};

LCDManager::LCDManager(Context* context): context(context) {}

bool LCDManager::addLCD(String name, String chip_id, int address, int rows, int cols, String type, int serverId) {
    DevicesController* devicesController = new DevicesController(context, storageType);
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::LCD, deviceEntity.id, serverId);
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
                + "/lcdmanager/add";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"address\":\"" 
                + String(address) + "\",\"rows\":\"" + String(rows) + "\",\"cols\":\"" 
                + String(cols) + "\",\"type\":\"" + String(type) + "\",\"server_id\":\"" + String(serverId) + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        LCDEntity lcdEntity = LCDEntity(module_id, address, rows, cols, type);
        LCDController* lcdController = new LCDController(context, storageType);
        lcdController->Add(lcdEntity);

        return true;
    }
    return false;
}

bool LCDManager::editLCD(int serverId, String name, String chip_id, int address, int rows, int cols, String type) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    DevicesController* devicesController = new DevicesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::LCD, deviceEntity.id, serverId);
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
                + "/lcdmanager/edit";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"address\":\"" 
                + String(address) + "\",\"rows\":\"" + String(rows) + "\",\"cols\":\"" 
                + String(cols) + "\",\"type\":\"" + String(type) + "\",\"server_id\":\"" + String(serverId) + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        LCDEntity lcdEntity = LCDEntity(module_id, address, rows, cols, type);
        LCDController* lcdController = new LCDController(context, storageType);
        lcdController->Update(lcdEntity);

        return true;
    }
    return false;
}

bool LCDManager::removeLCD(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Delete(serverId)) {
        return true;
    }
    return false;
}

LCDFullEntity* LCDManager::getLCDEntity(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getLCDByServerId(serverId);
}

std::vector<LCDFullEntity*> LCDManager::getAllLCDEntities() {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getAllLCDs();
}

#endif // LCDMANAGER_H
