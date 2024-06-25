#ifndef LCDENTITY_H
#define LCDENTITY_H

#include "../Entity.h"

class LCDEntity : public Entity {
public:
    static const String COLUMN_MODULEID;
    static const String COLUMN_ADDRESS;
    static const String COLUMN_ROWS;
    static const String COLUMN_COLS;
    static const String COLUMN_TYPE;
    
private:
    int _ModuleId;
    int _Address;
    int _Rows;
    int _Cols;
    String _Type;
    

public:
    LCDEntity()  : Entity(){}

    LCDEntity(int id, int ModuleId, int Address, int Rows, int Cols, String Type) : Entity() {
        this->id = id;
        _ModuleId = ModuleId;
        _Address = Address;
        _Rows = Rows;
        _Cols = Cols;
        _Type = Type;
        

        addColumn(COLUMN_MODULEID, String(ModuleId), "int");
        addColumn(COLUMN_ADDRESS, String(Address), "int");
        addColumn(COLUMN_ROWS, String(Rows), "int");
        addColumn(COLUMN_COLS, String(Cols), "int");
        addColumn(COLUMN_TYPE, String(Type), "String");
        
    }

    LCDEntity(int ModuleId, int Address, int Rows, int Cols, String Type) : 
        LCDEntity(0, _ModuleId, _Address, _Rows, _Cols, _Type)  {}

    static LCDEntity fromEntity(Entity entity)
    {
        LCDEntity lcdentity = LCDEntity();
        lcdentity.fromString(entity.toString());
        return lcdentity;
    }

    // Getters for each field
    int getModuleId() {
        return _ModuleId;
    }
    int getAddress() {
        return _Address;
    }
    int getRows() {
        return _Rows;
    }
    int getCols() {
        return _Cols;
    }
    String getType() {
        return _Type;
    }
    
    
    // Setters for each field
    void setModuleId(int ModuleId) {
        SetValue(COLUMN_MODULEID, String(ModuleId));
        _ModuleId = ModuleId;
    }
    void setAddress(int Address) {
        SetValue(COLUMN_ADDRESS, String(Address));
        _Address = Address;
    }
    void setRows(int Rows) {
        SetValue(COLUMN_ROWS, String(Rows));
        _Rows = Rows;
    }
    void setCols(int Cols) {
        SetValue(COLUMN_COLS, String(Cols));
        _Cols = Cols;
    }
    void setType(String Type) {
        SetValue(COLUMN_TYPE, String(Type));
        _Type = Type;
    }
    
};

const String LCDEntity::COLUMN_MODULEID = "ModuleId";
const String LCDEntity::COLUMN_ADDRESS = "Address";
const String LCDEntity::COLUMN_ROWS = "Rows";
const String LCDEntity::COLUMN_COLS = "Cols";
const String LCDEntity::COLUMN_TYPE = "Type";


#endif // LCDENTITY_H