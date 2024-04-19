#ifndef ACCOUNTLOCKOUTCONTROLLER_H
#define ACCOUNTLOCKOUTCONTROLLER_H

#include <OStad.h>
#include "../Entities/AccountLockoutEntity.h"
#include "../../AppContext.h"

class AccountLockoutController : public MainController<AccountLockoutEntity> {
public:
    AppContext* appContext;
    AccountLockoutController(AppContext* appContext, StorageType _storageType) : MainController<AccountLockoutEntity>(appContext->systemContext ,"accountlockout", _storageType), appContext(appContext) {}
};

#endif // ACCOUNTLOCKOUTCONTROLLER_H