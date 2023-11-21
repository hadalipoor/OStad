#ifndef TWOFACTORAUTHCONTROLLER_H
#define TWOFACTORAUTHCONTROLLER_H

#include <OStad.h>
#include "../../Entities/Security/TwoFactorAuthEntity.h"
#include "../../../Context.h"

class TwoFactorAuthController : public MainController<TwoFactorAuthEntity> {
public:
    Context* context;
    TwoFactorAuthController(Context* context, StorageType _storageType) : MainController<TwoFactorAuthEntity>(context ,"twofactorauth", _storageType), context(context) {}
};

#endif // TWOFACTORAUTHCONTROLLER_H