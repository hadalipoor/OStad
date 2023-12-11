
#ifndef AUTHENTICATIONCONFIGCONTROLLER_H
#define AUTHENTICATIONCONFIGCONTROLLER_H

#include "../../Entities/KeyValueEntity.h"
#include "../MainController.h"

class AuthenticationConfigController : public MainController<KeyValueEntity>{
protected:
    Context* context;
public:
    AuthenticationConfigController(Context* context, StorageType _storageType) : MainController<KeyValueEntity>(context ,"authentication_config", _storageType), context(context) {}

};

#endif //AUTHENTICATIONCONFIGCONTROLLER_H
    