#ifndef ACCOUNTACTIVITYLOGCONTROLLER_H
#define ACCOUNTACTIVITYLOGCONTROLLER_H

#include "../../Entities/Security/AccountActivityLogEntity.h"
#include "../../../Context.h"

class AccountActivityLogController : public MainController<AccountActivityLogEntity> {
public:
    Context* context;
    AccountActivityLogController(Context* context, StorageType _storageType) : MainController<AccountActivityLogEntity>(context ,"accountactivitylog", _storageType), context(context) {}
};

#endif // ACCOUNTACTIVITYLOGCONTROLLER_H