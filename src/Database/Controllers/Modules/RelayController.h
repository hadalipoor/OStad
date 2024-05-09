#ifndef RELAYCONTROLLER_H
#define RELAYCONTROLLER_H

#include "../../Entities/Modules/RelayEntity.h"
#include "../../Entities/Modules/RelayFullEntity.h"
#include "../MainController.h"

class RelayController : public MainController<RelayEntity> {
protected:
    Context* context;
public:
    RelayController(Context* context, StorageType _storageType) : MainController<RelayEntity>(context, "relay", _storageType), context(context) {}

};

#endif // RELAYCONTROLLER_H
