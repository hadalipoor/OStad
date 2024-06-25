#ifndef ILCDMANAGER_H
#define ILCDMANAGER_H

#include <vector>
#include "../Database/Entities/Modules/LCDFullEntity.h"

class ILCDManager {
public:
    virtual bool addLCD(String name, String chip_id, int address, int rows, int cols, String type, int serverId) = 0;
    virtual bool editLCD(int serverId, String name, String chip_id, int address, int rows, int cols, String type) = 0;
    virtual bool removeLCD(int serverId) = 0;
    virtual LCDFullEntity* getLCDEntity(int serverId) = 0;
    virtual std::vector<LCDFullEntity*> getAllLCDEntities() = 0;
};

#endif // ILCDMANAGER_H
