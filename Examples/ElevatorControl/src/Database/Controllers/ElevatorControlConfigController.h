
#ifndef ELEVATORCONTROLCONFIGCONTROLLER_H
#define ELEVATORCONTROLCONFIGCONTROLLER_H

#include "../../AppContext.h"

class ElevatorControlConfigController : public MainController<KeyValueEntity>{
protected:
public:
    AppContext* appContext;
    ElevatorControlConfigController(AppContext* appContext, StorageType _storageType) : MainController<KeyValueEntity>(appContext->systemContext ,"elevatorcontrol_config", _storageType), appContext(appContext) {}

};

#endif //ELEVATORCONTROLCONFIGCONTROLLER_H
    