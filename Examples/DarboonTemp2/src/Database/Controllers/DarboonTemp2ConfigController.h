#ifndef DARBOONTEMP2CONFIGCONTROLLER_H
#define DARBOONTEMP2CONFIGCONTROLLER_H

#include <OStad.h>
#include "../Entities/DarboonTemp2ConfigEntity.h"
#include "../../AppContext.h"

class DarboonTemp2ConfigController : public MainController<DarboonTemp2ConfigEntity> {
public:
    AppContext* appContext;
    DarboonTemp2ConfigController(AppContext* appContext, StorageType _storageType) : MainController<DarboonTemp2ConfigEntity>(appContext->systemContext ,"darboontemp2config", _storageType), appContext(appContext) {}
};

#endif // DARBOONTEMP2CONFIGCONTROLLER_H