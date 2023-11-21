#ifndef PLANTCONTROLLER_H
#define PLANTCONTROLLER_H

#include <OStad.h>
#include "../Entities/PlantEntity.h"
#include "../../AppContext.h"

class PlantController : public MainController<PlantEntity> {
public:
    AppContext* appContext;
    PlantController(AppContext* appContext, StorageType _storageType) : MainController<PlantEntity>(appContext->systemContext ,"plant", _storageType), appContext(appContext) {}
};

#endif // PLANTCONTROLLER_H