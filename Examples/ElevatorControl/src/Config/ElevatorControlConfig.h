
#ifndef ELEVATORCONTROLCONFIGS_H
#define ELEVATORCONTROLCONFIGS_H

#include <string>
#include "DefaultElevatorControlConfigs.h"
#include "../AppContext.h"
#include "../Database/Controllers/ElevatorControlConfigController.h"
#include "ElevatorControlConfigKeys.h"

class ElevatorControlConfig : public IConfig {

private:
    ElevatorControlConfigController* elevatorcontrolConfigController;

public:
    AppContext* appContext;
    ElevatorControlConfig(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        elevatorcontrolConfigController = new ElevatorControlConfigController(appContext, storageType);

    }

    String get(const String& key) {
        std::vector<KeyValueEntity> elevatorcontrolConfigEntities  = elevatorcontrolConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
        
        if (elevatorcontrolConfigEntities.size() > 0)
        {
            KeyValueEntity configEntity = elevatorcontrolConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            KeyValueEntity* keyValueEntity = new KeyValueEntity(key,DefaultElevatorControlConfigs::get(key));
            elevatorcontrolConfigController->Add(*keyValueEntity);
            return DefaultElevatorControlConfigs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        KeyValueEntity configEntity = elevatorcontrolConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            elevatorcontrolConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            elevatorcontrolConfigController->Update(configEntity);
        }
    }

};

#endif // ELEVATORCONTROL_H
