
#ifndef DEVICETESTCONFIGS_H
#define DEVICETESTCONFIGS_H

#include <string>
#include "DefaultDeviceTestConfigs.h"
#include "../AppContext.h"
#include "../Database/Controllers/DeviceTestConfigController.h"
#include "DeviceTestConfigKeys.h"

class DeviceTestConfig : public IConfig {

private:
    DeviceTestConfigController* devicetestConfigController;

public:
    AppContext* appContext;
    DeviceTestConfig(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        devicetestConfigController = new DeviceTestConfigController(appContext, storageType);
    }

    String get(const String& key) {
        std::vector<DeviceTestConfigEntity> devicetestConfigEntities  = devicetestConfigController->Get(DeviceTestConfigEntity::COLUMN_KEY + "=" + key);
        
        if (devicetestConfigEntities.size() > 0)
        {
            DeviceTestConfigEntity configEntity = devicetestConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            DeviceTestConfigEntity* devicetestConfigEntity = new DeviceTestConfigEntity(key,DefaultDeviceTestConfigs::get(key));
            devicetestConfigController->Add(*devicetestConfigEntity);
            return DefaultDeviceTestConfigs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        DeviceTestConfigEntity configEntity = devicetestConfigController->Get(DeviceTestConfigEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            devicetestConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            devicetestConfigController->Update(configEntity);
        }
    }

};

#endif // DEVICETEST_H
