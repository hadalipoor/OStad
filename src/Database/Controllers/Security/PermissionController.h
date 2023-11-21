#ifndef PERMISSIONCONTROLLER_H
#define PERMISSIONCONTROLLER_H

#include "../../Entities/Security/PermissionEntity.h"
#include "../../../Context.h"

class PermissionController : public MainController<PermissionEntity> {
public:
    Context* context;
    PermissionController(Context* context, StorageType _storageType) : MainController<PermissionEntity>(context ,"permission", _storageType), context(context) {}
};

#endif // PERMISSIONCONTROLLER_H