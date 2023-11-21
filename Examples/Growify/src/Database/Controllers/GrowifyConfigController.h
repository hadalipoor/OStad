
#ifndef GROWIFYCONFIGCONTROLLER_H
#define GROWIFYCONFIGCONTROLLER_H

#include "../../AppContext.h"

class GrowifyConfigController : public MainController<KeyValueEntity>{
protected:
public:
    AppContext* appContext;
    GrowifyConfigController(AppContext* appContext, StorageType _storageType) : MainController<KeyValueEntity>(appContext->systemContext ,"growify_config", _storageType), appContext(appContext) {}

};

#endif //GROWIFYCONFIGCONTROLLER_H
    