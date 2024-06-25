#ifndef RGBFULLENTITY_H
#define RGBFULLENTITY_H

#include "..\Entity.h"

class RGBFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    int PinNumber;
    String Type;
    int Rpin;
    int Gpin;
    int Bpin;
    int DeviceId;
    int ServerId;


    RGBFullEntity(int id, int moduleId, const String &_Name,
                  int pinNumber, const String &type, int rpin, int gpin, int bpin, int deviceId, int serverId) {
        this->id = id;
        Type = type;
        Rpin = rpin;
        Gpin = gpin;
        Bpin = bpin;
        ModuleId = moduleId;
        Name = _Name;
        PinNumber = pinNumber;
        DeviceId = deviceId;
        ServerId = serverId;    
    }

    RGBFullEntity(): RGBFullEntity(0, 0, "", 0, "", 0, 0, 0, 0, 0) {}
};

#endif // RGBFULLENTITY_H
