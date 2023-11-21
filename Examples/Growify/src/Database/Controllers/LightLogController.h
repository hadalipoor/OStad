#ifndef LIGHTLOGCONTROLLER_H
#define LIGHTLOGCONTROLLER_H

#include <OStad.h>
#include "../Entities/LightLogEntity.h"
#include "../../AppContext.h"

class LightLogController : public MainController<LightLogEntity> {
public:
    AppContext* appContext;
    LightLogController(AppContext* appContext, StorageType _storageType) : MainController<LightLogEntity>(appContext->systemContext ,"lightlog", _storageType), appContext(appContext) {}
};

#endif // LIGHTLOGCONTROLLER_H