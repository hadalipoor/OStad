#ifndef LCDFULLENTITY_H
#define LCDFULLENTITY_H

#include "..\Entity.h"

class LCDFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber;
    int Address;
    int Rows;
    int Cols;
    String Type;

    LCDFullEntity() {}

    LCDFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId,
                  int pinNumber, int address, int row, int col, const String &type) {
        this->id = id;
        Address = address;
        Rows = row;
        Cols = col;
        Type = type;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber = pinNumber;
    }
};

#endif // LCDFULLENTITY_H
