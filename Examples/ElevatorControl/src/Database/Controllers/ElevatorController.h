#ifndef ELEVATORCONTROLLER_H
#define ELEVATORCONTROLLER_H

#include <OStad.h>
#include "../Entities/ElevatorEntity.h"
#include "../../AppContext.h"

class ElevatorController : public MainController<ElevatorEntity> {
public:
    AppContext* appContext;
    ElevatorController(AppContext* appContext, StorageType _storageType) : MainController<ElevatorEntity>(appContext->systemContext ,"elevator", _storageType), appContext(appContext) {}
};

#endif // ELEVATORCONTROLLER_H