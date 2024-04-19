#ifndef TWOFACTORAUTHCONTROLLER_H
#define TWOFACTORAUTHCONTROLLER_H

#include <OStad.h>
#include "../Entities/TwoFactorAuthEntity.h"
#include "../../AppContext.h"

class TwoFactorAuthController : public MainController<TwoFactorAuthEntity> {
public:
    AppContext* appContext;
    TwoFactorAuthController(AppContext* appContext, StorageType _storageType) : MainController<TwoFactorAuthEntity>(appContext->systemContext ,"twofactorauth", _storageType), appContext(appContext) {}
};

#endif // TWOFACTORAUTHCONTROLLER_H