#ifndef REQUESTLOGCONTROLLER_H
#define REQUESTLOGCONTROLLER_H

#include <OStad.h>
#include "../Entities/RequestLogEntity.h"
#include "../../AppContext.h"

class RequestLogController : public MainController<RequestLogEntity> {
public:
    AppContext* appContext;
    RequestLogController(AppContext* appContext, StorageType _storageType) : MainController<RequestLogEntity>(appContext->systemContext ,"requestlog", _storageType), appContext(appContext) {}
};

#endif // REQUESTLOGCONTROLLER_H