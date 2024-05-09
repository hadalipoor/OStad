#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include <string>
#include "../../Database/Controllers/Configs/SystemConfigController.h"
#include "../../Database/Entities/KeyValueEntity.h"
#include "../IConfig.h"
#include "DefaultSystemConfigs.h"
#include "SystemConfigKeys.h"
#include "../../Context.h"

class SystemConfig : public IConfig {

private:
    Context* context;
    SystemConfigController* configController;

public:
    SystemConfig(Context* cntxt);
    void initialize() override;
    String get(const String& key) override;
    void set(const String& key, const String& value) override;
};

SystemConfig::SystemConfig(Context* cntxt):context (cntxt) {
}

void SystemConfig::initialize() {
    configController = new SystemConfigController(context, storageType);
}

String SystemConfig::get(const String& key) {
    
    std::vector<KeyValueEntity> systemConfigEntities  = configController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
    
    if (systemConfigEntities.size() > 0)
    {
        KeyValueEntity configEntity = systemConfigEntities.at(0);
        configEntity.fromString(configEntity.toString());
        if (configEntity.id == -1) {
            return "";
        } else {
            return configEntity.getValue();
        }
    }
    else
    {
        KeyValueEntity* systemConfigEntity = new KeyValueEntity(key,DefaultSystemConfigs::get(key));
        
        configController->Add(*systemConfigEntity);
        return DefaultSystemConfigs::get(key);
    }
}

void SystemConfig::set(const String& key, const String& value) {
    KeyValueEntity configEntity = configController->Get(KeyValueEntity::COLUMN_KEY + "=" + key).at(0);
    if (configEntity.id == -1) { // Key does not exist
        configEntity.setKey(key);
        configEntity.setValue(value);
        configController->Add(configEntity);
    } else { // Key exists
        configEntity.setValue(value);
        configController->Update(configEntity);
    }
}

#endif // SYSTEMCONFIG_H
