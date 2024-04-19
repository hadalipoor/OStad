#ifndef USERRESETPASSCONTROLLER_H
#define USERRESETPASSCONTROLLER_H

#include <OStad.h>
#include "../Entities/UserResetPassEntity.h"
#include "../../AppContext.h"

class UserResetPassController : public MainController<UserResetPassEntity> {
public:
    AppContext* appContext;
    UserResetPassController(AppContext* appContext, StorageType _storageType) : MainController<UserResetPassEntity>(appContext->systemContext ,"userresetpass", _storageType), appContext(appContext) {}
};

#endif // USERRESETPASSCONTROLLER_H