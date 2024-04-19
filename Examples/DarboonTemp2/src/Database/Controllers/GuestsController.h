#ifndef GUESTSCONTROLLER_H
#define GUESTSCONTROLLER_H

#include <OStad.h>
#include "../Entities/GuestsEntity.h"
#include "../../AppContext.h"

class GuestsController : public MainController<GuestsEntity> {
public:
    AppContext* appContext;
    GuestsController(AppContext* appContext, StorageType _storageType) : MainController<GuestsEntity>(appContext->systemContext ,"guests", _storageType), appContext(appContext) {}
};

#endif // GUESTSCONTROLLER_H