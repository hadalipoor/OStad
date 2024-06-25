#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include "IButtonManager.h"
#include "../Context.h"
#include "../Database/Controllers/Modules/DevicesController.h"
#include "../Database/Controllers/Modules/ModulesController.h"
#include "../Config/Device/DeviceConfigKeys.h"

class ButtonManager: public IButtonManager {
private:
    Context* context;
public:
    ButtonManager(Context* context);

    bool addButton(String name, String chip_id, uint8_t pinNumber, bool activeHigh, bool pullUpActive, int debounceDelay, int serverId) override;
    bool editButton(int serverId, String name, String chip_id, uint8_t pinNumber, bool activeHigh, bool pullUpActive, int debounceDelay) override;
    bool removeButton(int serverId) override;
    ButtonFullEntity* getButtonEntity(int serverId) override;
    std::vector<ButtonFullEntity*> getAllButtonEntities() override;
};

ButtonManager::ButtonManager(Context* context): context(context) {}

bool ButtonManager::addButton(String name, String chip_id, uint8_t pinNumber, bool activeHigh, bool pullUpActive, int debounceDelay, int serverId) {
    DevicesController* devicesController = new DevicesController(context, storageType);
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::BUTTON, deviceEntity.id, serverId);
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
                + "/buttonmanager/add";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number\":\"" 
                + String(pinNumber) + "\",\"server_id\":\"" + String(serverId) + "\",\"active_high\":\"" 
                + (activeHigh ? "true" : "false") + "\",\"pull_up_active\":\"" 
                + (pullUpActive ? "true" : "false") + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        ButtonEntity buttonEntity = ButtonEntity(module_id, "PIN", pinNumber, activeHigh, pullUpActive, debounceDelay);
        ButtonController* buttonController = new ButtonController(context, storageType);
        buttonController->Add(buttonEntity);

        return true;
    }
    return false;
}

bool ButtonManager::editButton(int serverId, String name, String chip_id, uint8_t pinNumber, bool activeHigh, bool pullUpActive, int debounceDelay) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    DevicesController* devicesController = new DevicesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME + String("=" + name)).size() == 0) {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if (deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::BUTTON, deviceEntity.id, serverId);
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
                + "/buttonmanager/edit";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number\":\"" 
                + String(pinNumber) + "\",\"server_id\":\"" + String(serverId) + "\",\"active_high\":\"" 
                + (activeHigh ? "true" : "false") + "\",\"pull_up_active\":\"" 
                + (pullUpActive ? "true" : "false") + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint, postData);
            // TODO: Check if response indicates failure and return false if so
        }

        ButtonEntity buttonEntity = ButtonEntity(module_id, "PIN", pinNumber, activeHigh, pullUpActive, debounceDelay);
        ButtonController* buttonController = new ButtonController(context, storageType);
        buttonController->Update(buttonEntity);

        return true;
    }
    return false;
}

bool ButtonManager::removeButton(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    if (moduleController->Delete(serverId)) {
        return true;
    }
    return false;
}

ButtonFullEntity* ButtonManager::getButtonEntity(int serverId) {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getButtonById(serverId);
}

std::vector<ButtonFullEntity*> ButtonManager::getAllButtonEntities() {
    ModulesController* moduleController = new ModulesController(context, storageType);
    return moduleController->getAllButtons();
}

#endif // BUTTONMANAGER_H
