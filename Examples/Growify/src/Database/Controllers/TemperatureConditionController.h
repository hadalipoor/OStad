#ifndef TEMPERATURECONDITIONCONTROLLER_H
#define TEMPERATURECONDITIONCONTROLLER_H

#include <OStad.h>
#include "../Entities/TemperatureConditionEntity.h"
#include "../../AppContext.h"

class TemperatureConditionController : public MainController<TemperatureConditionEntity> {
public:
    AppContext* appContext;
    TemperatureConditionController(AppContext* appContext, StorageType _storageType) : MainController<TemperatureConditionEntity>(appContext->systemContext ,"temperaturecondition", _storageType), appContext(appContext) {}
};

#endif // TEMPERATURECONDITIONCONTROLLER_H