#ifndef ISOILMOISTURESENSOR_H
#define ISOILMOISTURESENSOR_H

#include <string>
#include "../../Database/Entities/Modules/SoilMoistureFullEntity.h"

class ISoilMoistureSensor {
public:
    virtual ~ISoilMoistureSensor() {}
    virtual void initialize() = 0;
    virtual int readMoisture() = 0;
    virtual bool isDry() = 0;
    virtual bool isWet() = 0;
    virtual String getName() = 0;
    virtual String getConnectionType() = 0;
    virtual int getNodeId() = 0;
    virtual int getSensorPin() = 0;
    virtual int getDryThreshold() = 0;
    virtual int getWetThreshold() = 0;
    virtual SoilMoistureFullEntity* getEntity() = 0;

};

#endif //ISOILMOISTURESENSOR_H
