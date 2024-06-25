#ifndef ISOILMOISTURESENSOR_H
#define ISOILMOISTURESENSOR_H

#include "ModuleTypes.h"
#include "BaseModule.h"
#include "../../Database/Entities/Modules/SoilMoistureFullEntity.h"

class ISoilMoistureSensor: public BaseModule {
public:
    ISoilMoistureSensor(int module_id, int server_id, String name, String moduleType, int device_id):
        BaseModule(module_id, server_id, name, moduleType, device_id) {}

    virtual void initialize() = 0;
    virtual int readMoisture() = 0;
    virtual bool isDry() = 0;
    virtual bool isWet() = 0;

    virtual int getSensorPin() = 0;
    virtual int getDryThreshold() = 0;
    virtual int getWetThreshold() = 0;

    virtual SoilMoistureFullEntity* getEntity() = 0;
};

#endif // ISOILMOISTURESENSOR_H