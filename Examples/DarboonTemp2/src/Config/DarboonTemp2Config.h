
#ifndef DARBOONTEMP2CONFIGS_H
#define DARBOONTEMP2CONFIGS_H

#include <string>
#include "DefaultDarboonTemp2Configs.h"
#include "../AppContext.h"
#include "../Database/Controllers/DarboonTemp2ConfigController.h"
#include "DarboonTemp2ConfigKeys.h"

class DarboonTemp2Config : public IConfig {

private:
    DarboonTemp2ConfigController* darboontemp2ConfigController;

public:
    AppContext* appContext;
    DarboonTemp2Config(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        darboontemp2ConfigController = new DarboonTemp2ConfigController(appContext, storageType);
    }

    String get(const String& key) {
        std::vector<KeyValueEntity> darboontemp2ConfigEntities  = darboontemp2ConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
        
        if (darboontemp2ConfigEntities.size() > 0)
        {
            KeyValueEntity configEntity = darboontemp2ConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            KeyValueEntity* keyValueEntity = new KeyValueEntity(key,DefaultDarboonTemp2Configs::get(key));
            darboontemp2ConfigController->Add(*keyValueEntity);
            return DefaultDarboonTemp2Configs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        KeyValueEntity configEntity = darboontemp2ConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            darboontemp2ConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            darboontemp2ConfigController->Update(configEntity);
        }
    }

};

#endif // DARBOONTEMP2_H
