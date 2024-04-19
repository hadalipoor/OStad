#ifndef PERMISSIONCONTROLLER_H
#define PERMISSIONCONTROLLER_H

#include <OStad.h>
#include "../Entities/PermissionEntity.h"
#include "../../AppContext.h"

class PermissionController : public MainController<PermissionEntity> {
public:
    AppContext* appContext;
    PermissionController(AppContext* appContext, StorageType _storageType) : MainController<PermissionEntity>(appContext->systemContext ,"permission", _storageType), appContext(appContext) {}
};

#endif // PERMISSIONCONTROLLER_H