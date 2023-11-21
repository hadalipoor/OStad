#ifndef DHTFULLENTITY_H
#define DHTFULLENTITY_H

#include "..\Entity.h"

class DHTFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber;
    String Type;
    int DryTreshold;
    int WetTreshold;
    int CoolTreshold;
    int HotTreshold;

    DHTFullEntity() {}

    DHTFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId,
                  int pinNumber, const String &type, int dryTreshold, int wetTreshold, int coolTreshold, int hotTreshold) {
        this->id = id;
        Type = type;
        DryTreshold = dryTreshold;
        WetTreshold = wetTreshold;
        CoolTreshold = coolTreshold;
        HotTreshold = hotTreshold;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber = pinNumber;
    }
};

#endif // DHTFULLENTITY_H
