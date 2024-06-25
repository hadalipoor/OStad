#ifndef IBUTTONMANAGER_H
#define IBUTTONMANAGER_H

#include <vector>
#include "../Database/Entities/Modules/ButtonFullEntity.h"

class IButtonManager {
public:
    virtual bool addButton(String name, String chip_id, uint8_t pinNumber, bool activeHigh, bool pullUpActive, int debounceDelay, int serverId) = 0;
    virtual bool editButton(int serverId, String name, String chip_id, uint8_t pinNumber, bool activeHigh, bool pullUpActive, int debounceDelay) = 0;
    virtual bool removeButton(int serverId) = 0;
    virtual ButtonFullEntity* getButtonEntity(int serverId) = 0;
    virtual std::vector<ButtonFullEntity*> getAllButtonEntities() = 0;
};

#endif // IBUTTONMANAGER_H
