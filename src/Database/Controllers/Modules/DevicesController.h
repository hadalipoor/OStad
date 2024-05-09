#ifndef DEVICESCONTROLLER_H
#define DEVICESCONTROLLER_H

#include "../../Entities/Modules/DevicesEntity.h"
#include "../MainController.h"

class DevicesController : public MainController<DevicesEntity> {
public:
    Context* context;
    DevicesController(Context* context, StorageType _storageType) : MainController<DevicesEntity>(context ,"devices", _storageType), context(context) {}
};

#endif // DEVICESCONTROLLER_H