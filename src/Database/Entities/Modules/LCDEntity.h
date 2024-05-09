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

private:
    int moduleId;
    int address;
    int rows;
    int cols;
    String type;

public:
    LCDEntity() : Entity() {}

    LCDEntity(int id, int moduleId, int address, int row, int col, const String &_Type) : Entity() {
        this->id = id;
        this->moduleId = moduleId;
        this->address = address;
        this->rows = row;
        this->cols = col;
        this->type = _Type;
        SetValue(COLUMN_MODULE_ID, String(this->moduleId));
        SetValue(COLUMN_ADDRESS, String(this->address));
        SetValue(COLUMN_ROW, String(this->rows));
        SetValue(COLUMN_COL, String(this->cols));
        SetValue(COLUMN_TYPE, this->type);
    }

    LCDEntity(int moduleId, int address, int row, int col, const String &_Type) : 
        LCDEntity(0, moduleId, address, row, col, _Type) {}

    static LCDEntity fromEntity(Entity entity)
    {
        LCDEntity lcdEntity = LCDEntity();
        lcdEntity.fromString(entity.toString());
        return lcdEntity;
    }

    // Getters
    int getModuleId() {
        moduleId = GetValue(COLUMN_MODULE_ID).toInt();
        return moduleId;
    }

    int getAddress() {
        address = GetValue(COLUMN_ADDRESS).toInt();
        return address;
    }

    int getRows() {
        rows = GetValue(COLUMN_ROW).toInt();
        return rows;
    }

    int getCols() {
        cols = GetValue(COLUMN_COL).toInt();
        return cols;
    }

    String getType() {
        type = GetValue(COLUMN_TYPE);
        return type;
    }

    // Setters
    void setModuleId(int value) {
        moduleId = value;
        SetValue(COLUMN_MODULE_ID, String(moduleId));
    }

    void setAddress(int value) {
        address = value;
        SetValue(COLUMN_ADDRESS, String(address));
    }

    void setRows(int value) {
        rows = value;
        SetValue(COLUMN_ROW, String(rows));
    }

    void setCols(int value) {
        cols = value;
        SetValue(COLUMN_COL, String(cols));
    }

    void setType(const String &value) {
        type = value;
        SetValue(COLUMN_TYPE, type);
    }

};

const String LCDEntity::COLUMN_MODULE_ID = "ModuleId";
const String LCDEntity::COLUMN_ADDRESS = "Address";
const String LCDEntity::COLUMN_ROW = "Rows";
const String LCDEntity::COLUMN_COL = "Cols";
const String LCDEntity::COLUMN_TYPE = "Type";

#endif // LCDENTITY_H
