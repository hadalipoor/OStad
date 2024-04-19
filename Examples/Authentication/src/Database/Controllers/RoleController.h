#ifndef ROLECONTROLLER_H
#define ROLECONTROLLER_H

#include <OStad.h>
#include "../Entities/RoleEntity.h"
#include "../../AppContext.h"

class RoleController : public MainController<RoleEntity> {
public:
    AppContext* appContext;
    RoleController(AppContext* appContext, StorageType _storageType) : MainController<RoleEntity>(appContext->systemContext ,"role", _storageType), appContext(appContext) {}
};

#endif // ROLECONTROLLER_H