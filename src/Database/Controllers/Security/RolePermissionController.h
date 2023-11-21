#ifndef ROLEPERMISSIONCONTROLLER_H
#define ROLEPERMISSIONCONTROLLER_H

#include "../../Entities/Security/RolePermissionEntity.h"
#include "../../../Context.h"

class RolePermissionController : public MainController<RolePermissionEntity> {
public:
    Context* context;
    RolePermissionController(Context* context, StorageType _storageType) : MainController<RolePermissionEntity>(context ,"rolepermission", _storageType), context(context) {}
};

#endif // ROLEPERMISSIONCONTROLLER_H