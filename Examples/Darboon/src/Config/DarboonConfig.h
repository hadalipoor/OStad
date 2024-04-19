
#ifndef DARBOONCONFIGS_H
#define DARBOONCONFIGS_H

#include <string>
#include "DefaultDarboonConfigs.h"
#include "../AppContext.h"
#include "../Database/Controllers/DarboonConfigController.h"
#include "DarboonConfigKeys.h"

class DarboonConfig : public IConfig {

private:
    DarboonConfigController* darboonConfigController;

public:
    AppContext* appContext;
    DarboonConfig(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        darboonConfigController = new DarboonConfigController(appContext, storageType);
    }

    String get(const String& key) {
        std::vector<KeyValueEntity> darboonConfigEntities  = darboonConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
        
        if (darboonConfigEntities.size() > 0)
        {
            KeyValueEntity configEntity = darboonConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            KeyValueEntity* keyValueEntity = new KeyValueEntity(key,DefaultDarboonConfigs::get(key));
            darboonConfigController->Add(*keyValueEntity);
            return DefaultDarboonConfigs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        KeyValueEntity configEntity = darboonConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            darboonConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            darboonConfigController->Update(configEntity);
        }
    }

};

#endif // DARBOON_H
