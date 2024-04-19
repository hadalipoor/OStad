#ifndef RFIDCONTROLLER_H
#define RFIDCONTROLLER_H

#include "../../Entities/Modules/RFIDEntity.h"
#include "../MainController.h"

class RFIDController : public MainController<RFIDEntity> {
protected:
    Context* context;
public:
    RFIDController(Context* context, StorageType _storageType) : MainController<RFIDEntity>(context, "rfidmodules", _storageType), context(context) {}
};

#endif // RELAYCONTROLLER_H
