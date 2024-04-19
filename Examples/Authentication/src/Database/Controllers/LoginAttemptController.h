#ifndef LOGINATTEMPTCONTROLLER_H
#define LOGINATTEMPTCONTROLLER_H

#include <OStad.h>
#include "../Entities/LoginAttemptEntity.h"
#include "../../AppContext.h"

class LoginAttemptController : public MainController<LoginAttemptEntity> {
public:
    AppContext* appContext;
    LoginAttemptController(AppContext* appContext, StorageType _storageType) : MainController<LoginAttemptEntity>(appContext->systemContext ,"loginattempt", _storageType), appContext(appContext) {}
};

#endif // LOGINATTEMPTCONTROLLER_H