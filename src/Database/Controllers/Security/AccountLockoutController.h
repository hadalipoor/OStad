#ifndef ACCOUNTLOCKOUTCONTROLLER_H
#define ACCOUNTLOCKOUTCONTROLLER_H

#include "../../Entities/Security/AccountLockoutEntity.h"
#include "../../../Context.h"

class AccountLockoutController : public MainController<AccountLockoutEntity> {
public:
    Context* context;
    AccountLockoutController(Context* context, StorageType _storageType) : MainController<AccountLockoutEntity>(context ,"accountlockout", _storageType), context(context) {}
};

#endif // ACCOUNTLOCKOUTCONTROLLER_H