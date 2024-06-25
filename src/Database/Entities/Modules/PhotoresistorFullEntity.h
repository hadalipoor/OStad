#ifndef PHOTORESISTORFULLENTITY_H
#define PHOTORESISTORFULLENTITY_H

#include "..\Entity.h"

class PhotoresistorFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    int PinNumber;
    int LowTreshold;
    int HighTreshold;
    int DeviceId;
    int ServerId;


    PhotoresistorFullEntity(int id, int moduleId, const String &_Name,
                            int pinNumber, int lowTreshold, int highTreshold, int deviceId, int serverId) {
        this->id = id;
        LowTreshold = lowTreshold;
        HighTreshold = highTreshold;
        ModuleId = moduleId;
        Name = _Name;
        PinNumber = pinNumber;
        DeviceId = deviceId;
        ServerId = serverId;    
    }

    PhotoresistorFullEntity(): PhotoresistorFullEntity(0, 0, "", 0, 0, 0, 0, 0) {}
};

#endif // PHOTORESISTORFULLENTITY_H
