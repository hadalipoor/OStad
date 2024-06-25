#ifndef IDHTSENSORMANAGER_H
#define IDHTSENSORMANAGER_H

#include <vector>
#include "../Database/Entities/Modules/DHTFullEntity.h"

class IDHTSensorManager {
public:
    virtual bool addDHTSensor(String name, String chip_id, int pinNumber, String type, int serverId) = 0;
    virtual bool editDHTSensor(int serverId, String name, String chip_id, int pinNumber, String type) = 0;
    virtual bool removeDHTSensor(int serverId) = 0;
    virtual DHTFullEntity* getDHTSensorEntity(int serverId) = 0;
    virtual std::vector<DHTFullEntity*> getAllDHTSensorEntities() = 0;
};

#endif // IDHTSENSORMANAGER_H
