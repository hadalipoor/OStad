#ifndef DHTFULLENTITY_H
#define DHTFULLENTITY_H

#include "..\Entity.h"

class DHTFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    int PinNumber;
    String Type;
    int DryTreshold;
    int WetTreshold;
    int CoolTreshold;
    int HotTreshold;
    int ServerId;

    DHTFullEntity() {}

    DHTFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType,
                  int pinNumber, const String &type, int dryTreshold, int wetTreshold, int coolTreshold, int hotTreshold, int serverId) {
        this->id = id;
        Type = type;
        DryTreshold = dryTreshold;
        WetTreshold = wetTreshold;
        CoolTreshold = coolTreshold;
        HotTreshold = hotTreshold;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        PinNumber = pinNumber;
        ServerId = serverId;
    }
};

#endif // DHTFULLENTITY_H
