#ifndef RGBENTITY_H
#define RGBENTITY_H

#include "../Entity.h"

class RGBEntity : public Entity {
public:
    static const String COLUMN_MODULEID;
    static const String COLUMN_PINNUMBER;
    static const String COLUMN_TYPE;
    static const String COLUMN_RPIN;
    static const String COLUMN_GPIN;
    static const String COLUMN_BPIN;
    
private:
    int _ModuleId;
    int _PinNumber;
    String _Type;
    int _Rpin;
    int _Gpin;
    int _Bpin;
    

public:
    RGBEntity()  : Entity(){}

    RGBEntity(int id, int ModuleId, int PinNumber, String Type, int Rpin, int Gpin, int Bpin) : Entity() {
        this->id = id;
        _ModuleId = ModuleId;
        _PinNumber = PinNumber;
        _Type = Type;
        _Rpin = Rpin;
        _Gpin = Gpin;
        _Bpin = Bpin;
        

        addColumn(COLUMN_MODULEID, String(ModuleId), "int");
        addColumn(COLUMN_PINNUMBER, String(PinNumber), "int");
        addColumn(COLUMN_TYPE, String(Type), "String");
        addColumn(COLUMN_RPIN, String(Rpin), "int");
        addColumn(COLUMN_GPIN, String(Gpin), "int");
        addColumn(COLUMN_BPIN, String(Bpin), "int");
        
    }

    RGBEntity(int ModuleId, int PinNumber, String Type, int Rpin, int Gpin, int Bpin) : 
        RGBEntity(0, _ModuleId, _PinNumber, _Type, _Rpin, _Gpin, _Bpin)  {}

    static RGBEntity fromEntity(Entity entity)
    {
        RGBEntity rgbentity = RGBEntity();
        rgbentity.fromString(entity.toString());
        return rgbentity;
    }

    // Getters for each field
    int getModuleId() {
        return _ModuleId;
    }
    int getPinNumber() {
        return _PinNumber;
    }
    String getType() {
        return _Type;
    }
    int getRpin() {
        return _Rpin;
    }
    int getGpin() {
        return _Gpin;
    }
    int getBpin() {
        return _Bpin;
    }
    
    
    // Setters for each field
    void setModuleId(int ModuleId) {
        SetValue(COLUMN_MODULEID, String(ModuleId));
        _ModuleId = ModuleId;
    }
    void setPinNumber(int PinNumber) {
        SetValue(COLUMN_PINNUMBER, String(PinNumber));
        _PinNumber = PinNumber;
    }
    void setType(String Type) {
        SetValue(COLUMN_TYPE, String(Type));
        _Type = Type;
    }
    void setRpin(int Rpin) {
        SetValue(COLUMN_RPIN, String(Rpin));
        _Rpin = Rpin;
    }
    void setGpin(int Gpin) {
        SetValue(COLUMN_GPIN, String(Gpin));
        _Gpin = Gpin;
    }
    void setBpin(int Bpin) {
        SetValue(COLUMN_BPIN, String(Bpin));
        _Bpin = Bpin;
    }
    
};

const String RGBEntity::COLUMN_MODULEID = "ModuleId";
const String RGBEntity::COLUMN_PINNUMBER = "PinNumber";
const String RGBEntity::COLUMN_TYPE = "Type";
const String RGBEntity::COLUMN_RPIN = "Rpin";
const String RGBEntity::COLUMN_GPIN = "Gpin";
const String RGBEntity::COLUMN_BPIN = "Bpin";


#endif // RGBENTITY_H