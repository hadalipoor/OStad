#ifndef ELEVATORLOGCONTROLLER_H
#define ELEVATORLOGCONTROLLER_H

#include <OStad.h>
#include "../Entities/ElevatorLogEntity.h"
#include "../../AppContext.h"

class ElevatorLogController : public MainController<ElevatorLogEntity> {
public:
    AppContext* appContext;
    ElevatorLogController(AppContext* appContext, StorageType _storageType) : MainController<ElevatorLogEntity>(appContext->systemContext ,"elevatorlog", _storageType), appContext(appContext) {}
};

#endif // ELEVATORLOGCONTROLLER_H