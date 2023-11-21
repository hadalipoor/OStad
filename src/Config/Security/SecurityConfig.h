
#ifndef AUTHENTICATIONCONFIGS_H
#define AUTHENTICATIONCONFIGS_H

#include <string>
#include "DefaultSecurityConfigs.h"
#include "../../Context.h"
#include "../../Database/Controllers/Security/AuthenticationConfigController.h"
#include "SecurityConfigKeys.h"

class SecurityConfig : public IConfig {

private:
    AuthenticationConfigController* authenticationConfigController;

public:
    Context* context;
    SecurityConfig(Context* cntxt):context (cntxt) {
    }
    
    void initialize() {
        authenticationConfigController = new AuthenticationConfigController(context, storageType);
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
            KeyValueEntity* keyValueEntity = new KeyValueEntity(key,DefaultSecurityConfigs::get(key));
            authenticationConfigController->Add(*keyValueEntity);
            return DefaultSecurityConfigs::get(key);
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
