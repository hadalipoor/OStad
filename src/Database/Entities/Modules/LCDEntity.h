#ifndef LCDENTITY_H
#define LCDENTITY_H

#include "..\Entity.h"

class LCDEntity : public Entity {
public:
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_ADDRESS;
    static const String COLUMN_ROW;
    static const String COLUMN_COL;
    static const String COLUMN_TYPE;

    int ModuleId;
    int Address;
    int Rows;
    int Cols;
    String Type;

    LCDEntity() : Entity() {}

    LCDEntity(int id, int moduleId, int address, int row, int col, const String &_Type) : Entity() {
        this->id = id;
        ModuleId = moduleId;
        Address = address;
        Rows = row;
        Cols = col;
        Type = _Type;
        addColumn(COLUMN_ADDRESS, String(Address), "int");
        addColumn(COLUMN_ROW, String(Rows), "int");
        addColumn(COLUMN_COL, String(Cols), "int");
        addColumn(COLUMN_TYPE, Type, "string");
    }

    LCDEntity(int moduleId, int address, int row, int col, const String &_Type) : 
        LCDEntity(0, moduleId, address, row, col, _Type) {}

    static LCDEntity fromEntity(Entity entity)
    {
        LCDEntity lcdEntity = LCDEntity();
        lcdEntity.fromString(entity.toString());
        return lcdEntity;
    }

    // Setters and Getters for each field
};

const String LCDEntity::COLUMN_MODULE_ID = "ModuleId";
const String LCDEntity::COLUMN_ADDRESS = "Address";
const String LCDEntity::COLUMN_ROW = "Rows";
const String LCDEntity::COLUMN_COL = "Cols";
const String LCDEntity::COLUMN_TYPE = "Type";

#endif // LCDENTITY_H
