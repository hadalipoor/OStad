#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include "../../Entities/Modules/ButtonEntity.h"
#include "../MainController.h"

class ButtonController : public MainController<ButtonEntity> {
protected:
    Context* context;
public:
    ButtonController(Context* context, StorageType _storageType) : MainController<ButtonEntity>(context, "button", _storageType), context(context) {}
};

#endif // BUTTONCONTROLLER_H
