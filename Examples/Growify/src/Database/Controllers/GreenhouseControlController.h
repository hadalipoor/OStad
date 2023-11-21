#ifndef GREENHOUSECONTROLCONTROLLER_H
#define GREENHOUSECONTROLCONTROLLER_H

#include <OStad.h>
#include "../Entities/GreenhouseControlEntity.h"
#include "../../AppContext.h"

class GreenhouseControlController : public MainController<GreenhouseControlEntity> {
public:
    AppContext* appContext;
    GreenhouseControlController(AppContext* appContext, StorageType _storageType) : MainController<GreenhouseControlEntity>(appContext->systemContext ,"greenhousecontrol", _storageType), appContext(appContext) {}
};

#endif // GREENHOUSECONTROLCONTROLLER_H