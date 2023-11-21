#ifndef LIGHTCONDITIONCONTROLLER_H
#define LIGHTCONDITIONCONTROLLER_H

#include <OStad.h>
#include "../Entities/LightConditionEntity.h"
#include "../../AppContext.h"

class LightConditionController : public MainController<LightConditionEntity> {
public:
    AppContext* appContext;
    LightConditionController(AppContext* appContext, StorageType _storageType) : MainController<LightConditionEntity>(appContext->systemContext ,"lightcondition", _storageType), appContext(appContext) {}
};

#endif // LIGHTCONDITIONCONTROLLER_H