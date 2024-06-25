#ifndef LCDFULLENTITY_H
#define LCDFULLENTITY_H

#include "..\Entity.h"

class LCDFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    int Address;
    int Rows;
    int Cols;
    String Type;
    int DeviceId;
    int ServerId;


    LCDFullEntity(int id, int moduleId, const String &_Name, int address, int row, int col,
                const String &type, int deviceId, int serverId) {
        this->id = id;
        Address = address;
        Rows = row;
        Cols = col;
        Type = type;
        ModuleId = moduleId;
        Name = _Name;
        DeviceId = deviceId;
        ServerId = serverId;    
    }

    LCDFullEntity(): LCDFullEntity(0, 0, "", 0, 0, 0, "", 0, 0) {}
};

#endif // LCDFULLENTITY_H
