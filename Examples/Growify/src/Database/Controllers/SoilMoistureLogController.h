#ifndef SOILMOISTURELOGCONTROLLER_H
#define SOILMOISTURELOGCONTROLLER_H

#include <OStad.h>
#include "../Entities/SoilMoistureLogEntity.h"
#include "../../AppContext.h"

class SoilMoistureLogController : public MainController<SoilMoistureLogEntity> {
public:
    AppContext* appContext;
    SoilMoistureLogController(AppContext* appContext, StorageType _storageType) : MainController<SoilMoistureLogEntity>(appContext->systemContext ,"soilmoisturelog", _storageType), appContext(appContext) {}
};

#endif // SOILMOISTURELOGCONTROLLER_H