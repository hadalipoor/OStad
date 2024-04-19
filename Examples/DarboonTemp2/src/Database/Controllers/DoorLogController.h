#ifndef DOORLOGCONTROLLER_H
#define DOORLOGCONTROLLER_H

#include <OStad.h>
#include "../Entities/DoorLogEntity.h"
#include "../../AppContext.h"

class DoorLogController : public MainController<DoorLogEntity> {
public:
    AppContext* appContext;
    DoorLogController(AppContext* appContext, StorageType _storageType) : MainController<DoorLogEntity>(appContext->systemContext ,"doorlog", _storageType), appContext(appContext) {}
};

#endif // DOORLOGCONTROLLER_H