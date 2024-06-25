#ifndef SOILMOISTUREFULLENTITY_H
#define SOILMOISTUREFULLENTITY_H

#include "..\Entity.h"

class SoilMoistureFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    int PinNumber;
    int DryTreshold;
    int WetTreshold;
    String Type;
    int DeviceId;
    int ServerId;


    SoilMoistureFullEntity(int id, int moduleId, const String &_Name, int pinNumber, int dryTreshold, int wetTreshold,
                           const String &type, int deviceId, int serverId) {
        this->id = id;
        DryTreshold = dryTreshold;
        WetTreshold = wetTreshold;
        Type = type;
        ModuleId = moduleId;
        Name = _Name;
        PinNumber = pinNumber;
        DeviceId = deviceId;
        ServerId = serverId;    
    }

    SoilMoistureFullEntity(): SoilMoistureFullEntity(0, 0, "", 0, 0, 0, "", 0, 0) {}
};

#endif // SOILMOISTUREFULLENTITY_H
