#ifndef RELAYFULLENTITY_H
#define RELAYFULLENTITY_H

#include "..\Entity.h"

class RelayFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber;
    bool NormallyOpen;

    RelayFullEntity() {}

    RelayFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId,
                    int pinNumber, bool normallyOpen) {
        this->id = id;
        NormallyOpen = normallyOpen;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber = pinNumber;
    }
};

#endif // RELAYFULLENTITY_H
