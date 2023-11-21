#ifndef GREENHOUSESENSORCONTROLLER_H
#define GREENHOUSESENSORCONTROLLER_H

#include <OStad.h>
#include "../Entities/GreenhouseSensorEntity.h"
#include "../../AppContext.h"

class GreenhouseSensorController : public MainController<GreenhouseSensorEntity> {
public:
    AppContext* appContext;
    GreenhouseSensorController(AppContext* appContext, StorageType _storageType) : MainController<GreenhouseSensorEntity>(appContext->systemContext ,"greenhousesensor", _storageType), appContext(appContext) {}
};

#endif // GREENHOUSESENSORCONTROLLER_H