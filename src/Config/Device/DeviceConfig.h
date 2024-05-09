
#ifndef DEVICECONFIGS_H
#define DEVICECONFIGS_H

#include <string>
#include "DefaultDeviceConfigs.h"
#include "../../Context.h"
#include "../../Database/Controllers/Configs/DeviceConfigController.h"
#include "DeviceConfigKeys.h"

class DeviceConfig : public IConfig {

private:
    DeviceConfigController* deviceConfigController;

public:
    Context* context;
    DeviceConfig(Context* cntxt):context (cntxt) {
    }
    
    void initialize() {
        deviceConfigController = new DeviceConfigController(context, storageType);
    }

    String get(const String& key) {
        std::vector<DeviceConfigEntity> deviceConfigEntities  = deviceConfigController->Get(DeviceConfigEntity::COLUMN_KEY + "=" + key);
        
        if (deviceConfigEntities.size() > 0)
        {
            DeviceConfigEntity configEntity = deviceConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            DeviceConfigEntity* deviceConfigEntity = new DeviceConfigEntity(key,DefaultDeviceConfigs::get(key));
            deviceConfigController->Add(*deviceConfigEntity);
            return DefaultDeviceConfigs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        DeviceConfigEntity configEntity = deviceConfigController->Get(DeviceConfigEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            deviceConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            deviceConfigController->Update(configEntity);
        }
    }

};

#endif // DEVICETEST_H
