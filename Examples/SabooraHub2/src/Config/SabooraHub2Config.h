
#ifndef SABOORAHUB2CONFIGS_H
#define SABOORAHUB2CONFIGS_H

#include <string>
#include "DefaultSabooraHub2Configs.h"
#include "../AppContext.h"
#include "../Database/Controllers/SabooraHub2ConfigController.h"
#include "SabooraHub2ConfigKeys.h"

class SabooraHub2Config : public IConfig {

private:
    SabooraHub2ConfigController* saboorahub2ConfigController;

public:
    AppContext* appContext;
    SabooraHub2Config(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        saboorahub2ConfigController = new SabooraHub2ConfigController(appContext, storageType);
    }

    String get(const String& key) {
        std::vector<KeyValueEntity> saboorahub2ConfigEntities  = saboorahub2ConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
        
        if (saboorahub2ConfigEntities.size() > 0)
        {
            KeyValueEntity configEntity = saboorahub2ConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            KeyValueEntity* keyValueEntity = new KeyValueEntity(key,DefaultSabooraHub2Configs::get(key));
            saboorahub2ConfigController->Add(*keyValueEntity);
            return DefaultSabooraHub2Configs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        KeyValueEntity configEntity = saboorahub2ConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            saboorahub2ConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            saboorahub2ConfigController->Update(configEntity);
        }
    }

};

#endif // SABOORAHUB2_H
