#ifndef ROLECONTROLLER_H
#define ROLECONTROLLER_H

#include "../../Entities/Security/RoleEntity.h"
#include "../../../Context.h"

class RoleController : public MainController<RoleEntity> {
public:
    Context* context;
    RoleController(Context* context, StorageType _storageType) : MainController<RoleEntity>(context ,"role", _storageType), context(context) {}
};

#endif // ROLECONTROLLER_H