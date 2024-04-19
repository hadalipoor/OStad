#ifndef ROLEPERMISSIONCONTROLLER_H
#define ROLEPERMISSIONCONTROLLER_H

#include <OStad.h>
#include "../Entities/RolePermissionEntity.h"
#include "../../AppContext.h"

class RolePermissionController : public MainController<RolePermissionEntity> {
public:
    AppContext* appContext;
    RolePermissionController(AppContext* appContext, StorageType _storageType) : MainController<RolePermissionEntity>(appContext->systemContext ,"rolepermission", _storageType), appContext(appContext) {}
};

#endif // ROLEPERMISSIONCONTROLLER_H