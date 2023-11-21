#ifndef DHTCONTROLLER_H
#define DHTCONTROLLER_H

#include "../../Entities/Modules/DHTEntity.h"
#include "../MainController.h"

class DHTController : public MainController<DHTEntity> {
protected:
    Context* context;
public:
    DHTController(Context* context, StorageType _storageType) : MainController<DHTEntity>(context, "dht", _storageType), context(context) {}
};

#endif // DHTCONTROLLER_H
