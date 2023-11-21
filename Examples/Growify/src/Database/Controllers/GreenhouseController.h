#ifndef GREENHOUSECONTROLLER_H
#define GREENHOUSECONTROLLER_H

#include <OStad.h>
#include "../Entities/GreenhouseEntity.h"
#include "../../AppContext.h"

class GreenhouseController : public MainController<GreenhouseEntity> {
public:
    AppContext* appContext;
    GreenhouseController(AppContext* appContext, StorageType _storageType) : MainController<GreenhouseEntity>(appContext->systemContext ,"greenhouse", _storageType), appContext(appContext) {}
};

#endif // GREENHOUSECONTROLLER_H