#ifndef SOILMOISTURECONDITIONCONTROLLER_H
#define SOILMOISTURECONDITIONCONTROLLER_H

#include <OStad.h>
#include "../Entities/SoilMoistureConditionEntity.h"
#include "../../AppContext.h"

class SoilMoistureConditionController : public MainController<SoilMoistureConditionEntity> {
public:
    AppContext* appContext;
    SoilMoistureConditionController(AppContext* appContext, StorageType _storageType) : MainController<SoilMoistureConditionEntity>(appContext->systemContext ,"soilmoisturecondition", _storageType), appContext(appContext) {}
};

#endif // SOILMOISTURECONDITIONCONTROLLER_H