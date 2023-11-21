#ifndef HUMIDITYLOGCONTROLLER_H
#define HUMIDITYLOGCONTROLLER_H

#include <OStad.h>
#include "../Entities/HumidityLogEntity.h"
#include "../../AppContext.h"

class HumidityLogController : public MainController<HumidityLogEntity> {
public:
    AppContext* appContext;
    HumidityLogController(AppContext* appContext, StorageType _storageType) : MainController<HumidityLogEntity>(appContext->systemContext ,"humiditylog", _storageType), appContext(appContext) {}
};

#endif // HUMIDITYLOGCONTROLLER_H