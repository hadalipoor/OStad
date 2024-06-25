#ifndef ISOILMOISTURESENSORMANAGER_H
#define ISOILMOISTURESENSORMANAGER_H

#include <vector>
#include "../Database/Entities/Modules/SoilMoistureFullEntity.h"

class ISoilMoistureSensorManager {
public:
    virtual bool addSoilMoistureSensor(String name, String chip_id, int pinNumber, int dryThreshold, int wetThreshold, int serverId) = 0;
    virtual bool editSoilMoistureSensor(int serverId, String name, String chip_id, int pinNumber, int dryThreshold, int wetThreshold) = 0;
    virtual bool removeSoilMoistureSensor(int serverId) = 0;
    virtual SoilMoistureFullEntity* getSoilMoistureSensorEntity(int serverId) = 0;
    virtual std::vector<SoilMoistureFullEntity*> getAllSoilMoistureSensorEntities() = 0;
};

#endif // ISOILMOISTURESENSORMANAGER_H
