
#ifndef DARBOONCONFIGCONTROLLER_H
#define DARBOONCONFIGCONTROLLER_H

#include "../../AppContext.h"

class DarboonConfigController : public MainController<KeyValueEntity>{
protected:
public:
    AppContext* appContext;
    DarboonConfigController(AppContext* appContext, StorageType _storageType) : MainController<KeyValueEntity>(appContext->systemContext ,"darboon_config", _storageType), appContext(appContext) {}

};

#endif //DARBOONCONFIGCONTROLLER_H
    