#ifndef SOILMOISTUREENTITY_H
#define SOILMOISTUREENTITY_H

#include "../Entity.h"

class SoilMoistureEntity : public Entity {
public:
    static const String COLUMN_MODULEID;
    static const String COLUMN_PINNUMBER;
    static const String COLUMN_DRYTRESHOLD;
    static const String COLUMN_WETTRESHOLD;
    static const String COLUMN_TYPE;
    
private:
    int _ModuleId;
    int _PinNumber;
    int _DryTreshold;
    int _WetTreshold;
    String _Type;
    

public:
    SoilMoistureEntity()  : Entity(){}

    SoilMoistureEntity(int id, int ModuleId, int PinNumber, int DryTreshold, int WetTreshold, String Type) : Entity() {
        this->id = id;
        _ModuleId = ModuleId;
        _PinNumber = PinNumber;
        _DryTreshold = DryTreshold;
        _WetTreshold = WetTreshold;
        _Type = Type;
        

        addColumn(COLUMN_MODULEID, String(ModuleId), "int");
        addColumn(COLUMN_PINNUMBER, String(PinNumber), "int");
        addColumn(COLUMN_DRYTRESHOLD, String(DryTreshold), "int");
        addColumn(COLUMN_WETTRESHOLD, String(WetTreshold), "int");
        addColumn(COLUMN_TYPE, String(Type), "String");
        
    }

    SoilMoistureEntity(int ModuleId, int PinNumber, int DryTreshold, int WetTreshold, String Type) : 
        SoilMoistureEntity(0, _ModuleId, _PinNumber, _DryTreshold, _WetTreshold, _Type)  {}

    static SoilMoistureEntity fromEntity(Entity entity)
    {
        SoilMoistureEntity soilmoistureentity = SoilMoistureEntity();
        soilmoistureentity.fromString(entity.toString());
        return soilmoistureentity;
    }

    // Getters for each field
    int getModuleId() {
        return _ModuleId;
    }
    int getPinNumber() {
        return _PinNumber;
    }
    int getDryTreshold() {
        return _DryTreshold;
    }
    int getWetTreshold() {
        return _WetTreshold;
    }
    String getType() {
        return _Type;
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
    void setDryTreshold(int DryTreshold) {
        SetValue(COLUMN_DRYTRESHOLD, String(DryTreshold));
        _DryTreshold = DryTreshold;
    }
    void setWetTreshold(int WetTreshold) {
        SetValue(COLUMN_WETTRESHOLD, String(WetTreshold));
        _WetTreshold = WetTreshold;
    }
    void setType(String Type) {
        SetValue(COLUMN_TYPE, String(Type));
        _Type = Type;
    }
    
};

const String SoilMoistureEntity::COLUMN_MODULEID = "ModuleId";
const String SoilMoistureEntity::COLUMN_PINNUMBER = "PinNumber";
const String SoilMoistureEntity::COLUMN_DRYTRESHOLD = "DryTreshold";
const String SoilMoistureEntity::COLUMN_WETTRESHOLD = "WetTreshold";
const String SoilMoistureEntity::COLUMN_TYPE = "Type";


#endif // SOILMOISTUREENTITY_H