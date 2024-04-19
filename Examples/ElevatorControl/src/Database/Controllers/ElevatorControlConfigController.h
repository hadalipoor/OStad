
#ifndef ELEVATORCONTROLCONFIGCONTROLLER_H
#define ELEVATORCONTROLCONFIGCONTROLLER_H

#include "../../AppContext.h"
#include "../Entities/ElevatorControlConfigEntity.h"

class ElevatorControlConfigController : public MainController<ElevatorControlConfigEntity>{
protected:
public:
    AppContext* appContext;
    ElevatorControlConfigController(AppContext* appContext, StorageType _storageType) : MainController<ElevatorControlConfigEntity>(appContext->systemContext ,"elevatorcontrol_config", _storageType), appContext(appContext) {}

};

#endif //ELEVATORCONTROLCONFIGCONTROLLER_H
    