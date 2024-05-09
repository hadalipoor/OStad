
#ifndef DEVICECONFIGCONTROLLER_H
#define DEVICECONFIGCONTROLLER_H

#include "../../Entities/Configs/DeviceConfigEntity.h"
#include "../MainController.h"

class DeviceConfigController : public MainController<DeviceConfigEntity>{
protected:
public:
    Context* context;
    DeviceConfigController(Context* context, StorageType _storageType) : MainController<DeviceConfigEntity>(context ,"devicetest_config", _storageType), context(context) {}

};

#endif //DEVICETESTCONFIGCONTROLLER_H
    