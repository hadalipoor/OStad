#ifndef FLOORCONTROLLER_H
#define FLOORCONTROLLER_H

#include <OStad.h>
#include "../Entities/FloorEntity.h"
#include "../../AppContext.h"

class FloorController : public MainController<FloorEntity> {
public:
    AppContext* appContext;
    FloorController(AppContext* appContext, StorageType _storageType) : MainController<FloorEntity>(appContext->systemContext ,"floor", _storageType), appContext(appContext) {}
};

#endif // FLOORCONTROLLER_H