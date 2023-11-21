#ifndef PHOTORESISTORCONTROLLER_H
#define PHOTORESISTORCONTROLLER_H

#include "../../Entities/Modules/PhotoresistorEntity.h"
#include "../MainController.h"

class PhotoresistorController : public MainController<PhotoresistorEntity> {
protected:
    Context* context;
public:
    PhotoresistorController(Context* context, StorageType _storageType) : MainController<PhotoresistorEntity>(context, "photoresistor", _storageType), context(context) {}
};

#endif // PHOTORESISTORCONTROLLER_H
