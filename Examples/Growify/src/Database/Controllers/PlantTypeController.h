#ifndef PLANTTYPECONTROLLER_H
#define PLANTTYPECONTROLLER_H

#include <OStad.h>
#include "../Entities/PlantTypeEntity.h"
#include "../../AppContext.h"

class PlantTypeController : public MainController<PlantTypeEntity> {
public:
    AppContext* appContext;
    PlantTypeController(AppContext* appContext, StorageType _storageType) : MainController<PlantTypeEntity>(appContext->systemContext ,"planttype", _storageType), appContext(appContext) {}
};

#endif // PLANTTYPECONTROLLER_H