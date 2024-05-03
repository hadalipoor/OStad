#ifndef DEVICESCONTROLLER_H
#define DEVICESCONTROLLER_H

#include <OStad.h>
#include "../Entities/DevicesEntity.h"
#include "../../AppContext.h"

class DevicesController : public MainController<DevicesEntity> {
public:
    AppContext* appContext;
    DevicesController(AppContext* appContext, StorageType _storageType) : MainController<DevicesEntity>(appContext->systemContext ,"devices", _storageType), appContext(appContext) {}
};

#endif // DEVICESCONTROLLER_H