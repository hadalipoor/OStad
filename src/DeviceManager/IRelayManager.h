#ifndef IRELAYMANAGER_H
#define IRELAYMANAGER_H

#include "../Database/Entities/Modules/RelayFullEntity.h"

class IRelayManager
{
public:
    virtual bool addRelay(String name, String chip_id, int pinNumber, bool normallyOpen, int serverId) = 0;
    virtual bool editRelay(int serverId, String name, String chip_id, int pinNumber, bool normallyOpen) = 0;
    virtual bool removeRelay(int serverId) = 0;
    virtual RelayFullEntity* getRelayEntity(int server_id) = 0;
    virtual std::vector<RelayFullEntity> getAllRelayEntities() = 0;
};

#endif //IRELAYMANAGER_H