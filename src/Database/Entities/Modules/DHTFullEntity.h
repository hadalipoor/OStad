#ifndef DHTFULLENTITY_H
#define DHTFULLENTITY_H

#include "..\Entity.h"

class DHTFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    int PinNumber;
    String Type;
    int DryTreshold;
    int WetTreshold;
    int CoolTreshold;
    int HotTreshold;
    int DeviceId;
    int ServerId;



    DHTFullEntity(int id, int moduleId, const String &_Name, 
                  int pinNumber, const String &type, int dryTreshold, int wetTreshold, int coolTreshold, int hotTreshold, int deviceId, int serverId) {
        this->id = id;
        Type = type;
        DryTreshold = dryTreshold;
        WetTreshold = wetTreshold;
        CoolTreshold = coolTreshold;
        HotTreshold = hotTreshold;
        ModuleId = moduleId;
        Name = _Name;
        PinNumber = pinNumber;
        DeviceId = deviceId;
        ServerId = serverId;
    }
    
    DHTFullEntity(): DHTFullEntity(0, 0, "", 0, "", 0, 0, 0, 0, 0, 0) {}
};

#endif // DHTFULLENTITY_H
