#ifndef SOILMOISTUREFULLENTITY_H
#define SOILMOISTUREFULLENTITY_H

#include "..\Entity.h"

class SoilMoistureFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber;
    int DryTreshold;
    int WetTreshold;
    String Type;

    SoilMoistureFullEntity() {}

    SoilMoistureFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId,
                           int pinNumber, int dryTreshold, int wetTreshold, const String &type) {
        this->id = id;
        DryTreshold = dryTreshold;
        WetTreshold = wetTreshold;
        Type = type;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber = pinNumber;
    }
};

#endif // SOILMOISTUREFULLENTITY_H
