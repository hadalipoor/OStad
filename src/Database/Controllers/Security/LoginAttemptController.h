#ifndef LOGINATTEMPTCONTROLLER_H
#define LOGINATTEMPTCONTROLLER_H

#include "../../Entities/Security/LoginAttemptEntity.h"
#include "../../../Context.h"

class LoginAttemptController : public MainController<LoginAttemptEntity> {
public:
    Context* context;
    LoginAttemptController(Context* context, StorageType _storageType) : MainController<LoginAttemptEntity>(context ,"loginattempt", _storageType), context(context) {}
};

#endif // LOGINATTEMPTCONTROLLER_H