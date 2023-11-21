
#ifndef INKJETPRINTERCONFIGS_H
#define INKJETPRINTERCONFIGS_H

#include <string>
#include "DefaultInkjetPrinterConfigs.h"
#include "../AppContext.h"
#include "../Database/Controllers/InkjetPrinterConfigController.h"
#include "InkjetPrinterConfigKeys.h"

class InkjetPrinterConfig : public IConfig {

private:
    InkjetPrinterConfigController* inkjetprinterConfigController;

public:
    AppContext* appContext;
    InkjetPrinterConfig(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        inkjetprinterConfigController = new InkjetPrinterConfigController(appContext, storageType);
    }

    String get(const String& key) {
        std::vector<KeyValueEntity> inkjetprinterConfigEntities  = inkjetprinterConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
        
        if (inkjetprinterConfigEntities.size() > 0)
        {
            KeyValueEntity configEntity = inkjetprinterConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            KeyValueEntity* keyValueEntity = new KeyValueEntity(key,DefaultInkjetPrinterConfigs::get(key));
            inkjetprinterConfigController->Add(*keyValueEntity);
            return DefaultInkjetPrinterConfigs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        KeyValueEntity configEntity = inkjetprinterConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            inkjetprinterConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            inkjetprinterConfigController->Update(configEntity);
        }
    }

};

#endif // INKJETPRINTER_H
