#ifndef HUMIDITYCONDITIONCONTROLLER_H
#define HUMIDITYCONDITIONCONTROLLER_H

#include <OStad.h>
#include "../Entities/HumidityConditionEntity.h"
#include "../../AppContext.h"

class HumidityConditionController : public MainController<HumidityConditionEntity> {
public:
    AppContext* appContext;
    HumidityConditionController(AppContext* appContext, StorageType _storageType) : MainController<HumidityConditionEntity>(appContext->systemContext ,"humiditycondition", _storageType), appContext(appContext) {}
};

#endif // HUMIDITYCONDITIONCONTROLLER_H