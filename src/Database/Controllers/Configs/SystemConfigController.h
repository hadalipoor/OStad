#ifndef SYSTEMCONFIGCONTROLLER_H
#define SYSTEMCONFIGCONTROLLER_H

#include "../../Entities/KeyValueEntity.h"
#include "../MainController.h"

class SystemConfigController : public MainController<KeyValueEntity>{
protected:
    Context* context;
public:
    SystemConfigController(Context* context, StorageType _storageType) : MainController<KeyValueEntity>(context ,"system_config", _storageType), context(context) {}    
};


#endif // SYSTEMCONFIGCONTROLLER_H
