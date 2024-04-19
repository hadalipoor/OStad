
#ifndef SABOORATANKERCONFIGCONTROLLER_H
#define SABOORATANKERCONFIGCONTROLLER_H

#include "../../AppContext.h"

class SabooraTankerConfigController : public MainController<KeyValueEntity>{
protected:
public:
    AppContext* appContext;
    SabooraTankerConfigController(AppContext* appContext, StorageType _storageType) : MainController<KeyValueEntity>(appContext->systemContext ,"sabooratanker_config", _storageType), appContext(appContext) {}

};

#endif //SABOORATANKERCONFIGCONTROLLER_H
    