#ifndef TEMPERATURELOGCONTROLLER_H
#define TEMPERATURELOGCONTROLLER_H

#include <OStad.h>
#include "../Entities/TemperatureLogEntity.h"
#include "../../AppContext.h"

class TemperatureLogController : public MainController<TemperatureLogEntity> {
public:
    AppContext* appContext;
    TemperatureLogController(AppContext* appContext, StorageType _storageType) : MainController<TemperatureLogEntity>(appContext->systemContext ,"temperaturelog", _storageType), appContext(appContext) {}
};

#endif // TEMPERATURELOGCONTROLLER_H