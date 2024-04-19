
#ifndef AUTHENTICATIONCONFIGCONTROLLER_H
#define AUTHENTICATIONCONFIGCONTROLLER_H

#include "../../AppContext.h"

class AuthenticationConfigController : public MainController<KeyValueEntity>{
protected:
public:
    AppContext* appContext;
    AuthenticationConfigController(AppContext* appContext, StorageType _storageType) : MainController<KeyValueEntity>(appContext->systemContext ,"authentication_config", _storageType), appContext(appContext) {}

};

#endif //AUTHENTICATIONCONFIGCONTROLLER_H
    