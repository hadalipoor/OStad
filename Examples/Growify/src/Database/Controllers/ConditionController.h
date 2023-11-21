#ifndef CONDITIONCONTROLLER_H
#define CONDITIONCONTROLLER_H

#include <OStad.h>
#include "../Entities/ConditionEntity.h"
#include "../../AppContext.h"

class ConditionController : public MainController<ConditionEntity> {
public:
    AppContext* appContext;
    ConditionController(AppContext* appContext, StorageType _storageType) : MainController<ConditionEntity>(appContext->systemContext ,"condition", _storageType), appContext(appContext) {}
};

#endif // CONDITIONCONTROLLER_H