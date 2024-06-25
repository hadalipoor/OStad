#ifndef RFIDFULLENTITY_H
#define RFIDFULLENTITY_H

#include "..\Entity.h"
#include "..\..\..\ModuleManager\Modules\ModuleTypes.h"

class RFIDFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    int PinNumber0;
    int PinNumber1;
    int DeviceId;
    int ServerId;
    String RFIDType;


    RFIDFullEntity(int id, int moduleId, const String &_Name,
                    int pinNumber0, int pinNumber1, int deviceId, int serverId) {
        this->id = id;
        ModuleId = moduleId;
        Name = _Name;
        PinNumber0 = pinNumber0;
        PinNumber1 = pinNumber1;
        DeviceId = deviceId;
        ServerId = serverId;    
        RFIDType = ModuleTypes::RFID125KH;
    }

    RFIDFullEntity(int id, int moduleId, const String &_Name,
                    int pinNumber, int deviceId, int serverId): RFIDFullEntity(id, moduleId, _Name, pinNumber, 0, deviceId, serverId)
    {
        RFIDType = ModuleTypes::RFIDPN532;
    }
    
    RFIDFullEntity():RFIDFullEntity(0, 0, "", 0, 0, 0) 
    {
        RFIDType = ModuleTypes::RFID125KH;
    }
};

#endif // RELAYFULLENTITY_H
