#ifndef RGBFULLENTITY_H
#define RGBFULLENTITY_H

#include "..\Entity.h"

class RGBFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber;
    String Type;
    int Rpin;
    int Gpin;
    int Bpin;

    RGBFullEntity() {}

    RGBFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId,
                  int pinNumber, const String &type, int rpin, int gpin, int bpin) {
        this->id = id;
        Type = type;
        Rpin = rpin;
        Gpin = gpin;
        Bpin = bpin;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber = pinNumber;
    }
};

#endif // RGBFULLENTITY_H
