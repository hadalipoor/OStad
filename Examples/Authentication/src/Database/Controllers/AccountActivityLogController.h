#ifndef ACCOUNTACTIVITYLOGCONTROLLER_H
#define ACCOUNTACTIVITYLOGCONTROLLER_H

#include <OStad.h>
#include "../Entities/AccountActivityLogEntity.h"
#include "../../AppContext.h"

class AccountActivityLogController : public MainController<AccountActivityLogEntity> {
public:
    AppContext* appContext;
    AccountActivityLogController(AppContext* appContext, StorageType _storageType) : MainController<AccountActivityLogEntity>(appContext->systemContext ,"accountactivitylog", _storageType), appContext(appContext) {}
};

#endif // ACCOUNTACTIVITYLOGCONTROLLER_H