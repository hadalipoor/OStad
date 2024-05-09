#ifndef RELAYMANAGER_H
#define RELAYMANAGER_H

#include "IRelayManager.h"
#include "../Context.h"
#include "../Database/Controllers/Modules/DevicesController.h"
#include "../Database/Controllers/Modules/ModulesController.h"
#include "../Config/Device/DeviceConfigKeys.h"

class RelayManager: public IRelayManager
{
private:
    Context* context;
public:
    RelayManager(Context* context);
    
    bool addRelay(String name, String chip_id, int pinNumber, bool normallyOpen, int serverId) override;
    bool editRelay(int serverId, String name, String chip_id, int pinNumber, bool normallyOpen) override;
    bool removeRelay(int serverId) override;
    RelayFullEntity* getRelayEntity(int server_id) override;
    std::vector<RelayFullEntity> getAllRelayEntities() override;
};

RelayManager::RelayManager(Context* context): context(context)
{
    
}

bool RelayManager::addRelay(String name, String chip_id, int pinNumber, bool normallyOpen, int serverId)
{
    ModulesController* moduleController = new ModulesController(context, storageType);
    DevicesController* devicesController = new DevicesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME+String("="+name)).size() == 0)
    {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if(deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::RELAY, deviceEntity.id, serverId);
        int module_id = moduleController->Add(moduleEntity);
        if (serverId == 0)
        {
            moduleEntity.setServerId(module_id);
            moduleEntity.id = module_id;
            moduleEntity.setServerId(module_id);
            serverId = module_id;
            moduleController->Update(moduleEntity);
        }
        
        if(chip_id != context->getDeviceManager()->chipId)
        {
            String endpoint = String(context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE)) + "://" 
                + deviceEntity.GetValue(DevicesEntity::COLUMN_IP) 
                + "/relaymanager/add";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number\":\"" 
                + String(pinNumber) + "\",\"server_id\":\"" + String(serverId) + "\",\"normally_open\":\"" 
                + (normallyOpen ? "true" : "false") + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint,postData);
            //TODO: check if succesful is false, return
        }
        RelayEntity relayEntity = RelayEntity(module_id, pinNumber, normallyOpen);
        RelayController* relayController = new RelayController(context, storageType);
        relayController->Add(relayEntity);

        return true;
    }
    return false;
    
}

bool RelayManager::editRelay(int serverId, String name, String chip_id, int pinNumber, bool normallyOpen)
{
    ModulesController* moduleController = new ModulesController(context, storageType);
    DevicesController* devicesController = new DevicesController(context, storageType);
    if (moduleController->Get(ModuleEntity::COLUMN_NAME+String("="+name)).size() == 0)
    {
        std::vector<DevicesEntity> deviceEntities = devicesController->Get(DevicesEntity::COLUMN_CHIPID + "=" + chip_id);
        if(deviceEntities.size() == 0) return false;

        DevicesEntity deviceEntity = deviceEntities.at(0);
        if (!deviceEntity.isValid) return false;
        ModuleEntity moduleEntity = ModuleEntity(name, ModuleTypes::RELAY, deviceEntity.id, serverId);
        int module_id = moduleController->Add(moduleEntity);
        if (serverId == 0)
        {
            moduleEntity.setServerId(module_id);
            moduleEntity.id = module_id;
            moduleEntity.setServerId(module_id);
            serverId = module_id;
            moduleController->Update(moduleEntity);
        }
        
        if(chip_id != context->getDeviceManager()->chipId)
        {
            String endpoint = String(context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE)) + "://" 
                + deviceEntity.GetValue(DevicesEntity::COLUMN_IP) 
                + "/relaymanager/add";
            String postData = "{\"chip_id\":\"" + String(chip_id) + "\",\"name\":\"" + String(name) + "\",\"pin_number\":\"" 
                + String(pinNumber) + "\",\"server_id\":\"" + String(serverId) + "\",\"normally_open\":\"" 
                + (normallyOpen ? "true" : "false") + "\"}";
            String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint,postData);
            //TODO: check if succesful is false, return
        }
        RelayEntity relayEntity = RelayEntity(module_id, pinNumber, normallyOpen);
        RelayController* relayController = new RelayController(context, storageType);
        relayController->Add(relayEntity);

        return true;
    }
}

bool RelayManager::removeRelay(int serverId)
{
    ModulesController* moduleController = new ModulesController(context, storageType);
    RelayController* relayController = new RelayController(context, storageType);
    RelayFullEntity relayFullEntity = moduleController->getRelayByServerId(serverId);
    relayController->Delete(relayFullEntity.id);
    moduleController->Delete(relayFullEntity.ModuleId);

    DevicesController* devicesController = new DevicesController(context, storageType);
    DevicesEntity deviceEntity = devicesController->GetById(relayFullEntity.DeviceId);
    if(deviceEntity.getChipId() != context->getDeviceManager()->chipId)
    {
        String endpoint = String(context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE)) + "://" 
            + deviceEntity.getIP() 
            + "/relaymanager/remove";
        String postData = "{\"server_id\": \"" + String(serverId) + "\"}";
        String response = context->getNetwork()->getApiManager()->makePostRequest(endpoint,postData);

    }
    return true;
}

RelayFullEntity* RelayManager::getRelayEntity(int server_id)
{
    ModulesController* modulesController = new ModulesController(context, storageType);
    DevicesController* devicesController = new DevicesController(context, storageType);
    DevicesEntity device = devicesController->GetById(modulesController->getRelayByServerId(server_id).DeviceId);
    String endpoint = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE) + device.GetValue(DevicesEntity::COLUMN_IP) + "/relaymanager/get_entity?server_id="+server_id;
    
    String response = context->getNetwork()->getApiManager()->makeGetRequest(endpoint);
}

std::vector<RelayFullEntity> RelayManager::getAllRelayEntities()
{
    ModulesController* modulesController = new ModulesController(context, storageType);
    return modulesController->getAllRelays();
}

#endif //RELAYMANAGER_H