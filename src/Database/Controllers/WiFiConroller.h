#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H

#include "../Entities/WiFiEntity.h"
#include "MainController.h"

class WiFiController : public MainController<WiFiEntity> {
protected:
    Context* context;
public:
    WiFiController(Context* context, StorageType _storageType) : MainController<WiFiEntity>(context, "wifi", _storageType), context(context) {}
};

#endif // WIFICONTROLLER_H
