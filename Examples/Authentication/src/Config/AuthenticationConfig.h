
#ifndef AUTHENTICATIONCONFIGS_H
#define AUTHENTICATIONCONFIGS_H

#include <string>
#include "DefaultAuthenticationConfigs.h"
#include "../AppContext.h"
#include "../Database/Controllers/AuthenticationConfigController.h"
#include "AuthenticationConfigKeys.h"

class AuthenticationConfig : public IConfig {

private:
    AuthenticationConfigController* authenticationConfigController;

public:
    AppContext* appContext;
    AuthenticationConfig(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        authenticationConfigController = new AuthenticationConfigController(appContext, storageType);
    }

    String get(const String& key) {
        std::vector<KeyValueEntity> authenticationConfigEntities  = authenticationConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
        
        if (authenticationConfigEntities.size() > 0)
        {
            KeyValueEntity configEntity = authenticationConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            KeyValueEntity* keyValueEntity = new KeyValueEntity(key,DefaultAuthenticationConfigs::get(key));
            authenticationConfigController->Add(*keyValueEntity);
            return DefaultAuthenticationConfigs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        KeyValueEntity configEntity = authenticationConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            authenticationConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            authenticationConfigController->Update(configEntity);
        }
    }

};

#endif // AUTHENTICATION_H
