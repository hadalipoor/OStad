#ifndef RGBCONTROLLER_H
#define RGBCONTROLLER_H

#include "../../Entities/Modules/RGBEntity.h"
#include "../MainController.h"

class RGBController : public MainController<RGBEntity> {
protected:
    Context* context;
public:
    RGBController(Context* context, StorageType _storageType) : MainController<RGBEntity>(context, "rgb", _storageType), context(context) {}
};

#endif // RGBCONTROLLER_H
