
#ifndef SABOORAHUB2CONFIGCONTROLLER_H
#define SABOORAHUB2CONFIGCONTROLLER_H

#include "../../AppContext.h"

class SabooraHub2ConfigController : public MainController<KeyValueEntity>{
protected:
public:
    AppContext* appContext;
    SabooraHub2ConfigController(AppContext* appContext, StorageType _storageType) : MainController<KeyValueEntity>(appContext->systemContext ,"saboorahub2_config", _storageType), appContext(appContext) {}

};

#endif //SABOORAHUB2CONFIGCONTROLLER_H
    