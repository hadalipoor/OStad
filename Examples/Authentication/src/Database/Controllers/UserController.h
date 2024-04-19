#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <OStad.h>
#include "../Entities/UserEntity.h"
#include "../../AppContext.h"

class UserController : public MainController<UserEntity> {
public:
    AppContext* appContext;
    UserController(AppContext* appContext, StorageType _storageType) : MainController<UserEntity>(appContext->systemContext ,"user", _storageType), appContext(appContext) {}
};

#endif // USERCONTROLLER_H