#ifndef RFIDFULLENTITY_H
#define RFIDFULLENTITY_H

#include "..\Entity.h"

class RFIDFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber0;
    int PinNumber1;

    RFIDFullEntity() {}

    RFIDFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId,
                    int pinNumber0, int pinNumber1) {
        this->id = id;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber0 = pinNumber0;
        PinNumber1 = pinNumber1;
    }

    RFIDFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId,
                    int pinNumber): RFIDFullEntity(id, moduleId, _Name, _ModuleType, _ConnectionType, nodeId, pinNumber, 0){}
};

#endif // RELAYFULLENTITY_H
