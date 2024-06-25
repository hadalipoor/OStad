#ifndef IRFIDMANAGER_H
#define IRFIDMANAGER_H

#include <vector>
#include "../Database/Entities/Modules/RFIDFullEntity.h"

class IRFIDManager {
public:
    virtual bool addRFID(String name, String chip_id, int pinNumber1, int pinNumber2, String type, int serverId) = 0;
    virtual bool editRFID(int serverId, String name, String chip_id, int pinNumber1, int pinNumber2, String type) = 0;
    virtual bool removeRFID(int serverId) = 0;
    virtual RFIDFullEntity* getRFIDEntity(int serverId) = 0;
    virtual std::vector<RFIDFullEntity*> getAllRFIDEntities() = 0;
};
#endif // IRFIDMANAGER_H
