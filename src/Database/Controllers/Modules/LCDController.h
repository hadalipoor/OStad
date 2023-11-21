#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

#include "../../Entities/Modules/LCDEntity.h"
#include "../MainController.h"

class LCDController : public MainController<LCDEntity> {
protected:
    Context* context;
public:
    LCDController(Context* context, StorageType _storageType) : MainController<LCDEntity>(context, "lcd", _storageType), context(context) {}
};

#endif // LCDCONTROLLER_H
