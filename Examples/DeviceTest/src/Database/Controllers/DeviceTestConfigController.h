
#ifndef DEVICETESTCONFIGCONTROLLER_H
#define DEVICETESTCONFIGCONTROLLER_H

#include "../../AppContext.h"
#include "../Entities/DeviceTestConfigEntity.h"

class DeviceTestConfigController : public MainController<DeviceTestConfigEntity>{
protected:
public:
    AppContext* appContext;
    DeviceTestConfigController(AppContext* appContext, StorageType _storageType) : MainController<DeviceTestConfigEntity>(appContext->systemContext ,"devicetest_config", _storageType), appContext(appContext) {}

};

#endif //DEVICETESTCONFIGCONTROLLER_H
    