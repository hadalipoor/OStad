#ifndef PHOTORESISTORFULLENTITY_H
#define PHOTORESISTORFULLENTITY_H

#include "..\Entity.h"

class PhotoresistorFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber;
    int LowTreshold;
    int HighTreshold;

    PhotoresistorFullEntity() {}

    PhotoresistorFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId,
                            int pinNumber, int lowTreshold, int highTreshold) {
        this->id = id;
        LowTreshold = lowTreshold;
        HighTreshold = highTreshold;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber = pinNumber;
    }
};

#endif // PHOTORESISTORFULLENTITY_H
