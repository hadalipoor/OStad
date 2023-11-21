#ifndef SOILMOISTURECONTROLLER_H
#define SOILMOISTURECONTROLLER_H

#include "../../Entities/Modules/SoilMoistureEntity.h"
#include "../MainController.h"

class SoilMoistureController : public MainController<SoilMoistureEntity> {
protected:
    Context* context;
public:
    SoilMoistureController(Context* context, StorageType _storageType) : MainController<SoilMoistureEntity>(context, "soilmoisture", _storageType), context(context) {}
};

#endif // SOILMOISTURECONTROLLER_H
