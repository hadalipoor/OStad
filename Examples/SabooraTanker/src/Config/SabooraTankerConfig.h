
#ifndef SABOORATANKERCONFIGS_H
#define SABOORATANKERCONFIGS_H

#include <string>
#include "DefaultSabooraTankerConfigs.h"
#include "../AppContext.h"
#include "../Database/Controllers/SabooraTankerConfigController.h"
#include "SabooraTankerConfigKeys.h"

class SabooraTankerConfig : public IConfig {

private:
    SabooraTankerConfigController* sabooratankerConfigController;

public:
    AppContext* appContext;
    SabooraTankerConfig(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        sabooratankerConfigController = new SabooraTankerConfigController(appContext, storageType);
    }

    String get(const String& key) {
        std::vector<KeyValueEntity> sabooratankerConfigEntities  = sabooratankerConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
        
        if (sabooratankerConfigEntities.size() > 0)
        {
            KeyValueEntity configEntity = sabooratankerConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            KeyValueEntity* keyValueEntity = new KeyValueEntity(key,DefaultSabooraTankerConfigs::get(key));
            sabooratankerConfigController->Add(*keyValueEntity);
            return DefaultSabooraTankerConfigs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        KeyValueEntity configEntity = sabooratankerConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            sabooratankerConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            sabooratankerConfigController->Update(configEntity);
        }
    }

};

#endif // SABOORATANKER_H
