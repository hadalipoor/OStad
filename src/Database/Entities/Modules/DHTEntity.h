#ifndef DHTENTITY_H
#define DHTENTITY_H

#include "../Entity.h"

class DHTEntity : public Entity {
public:
    static const String COLUMN_MODULEID;
    static const String COLUMN_TYPE;
    static const String COLUMN_PINNUMBER;
    static const String COLUMN_DRYTRESHOLD;
    static const String COLUMN_WETTRESHOLD;
    static const String COLUMN_COOLTRESHOLD;
    static const String COLUMN_HOTTRESHOLD;
    
private:
    int _ModuleId;
    String _Type;
    int _PinNumber;
    int _DryTreshold;
    int _WetTreshold;
    int _CoolTreshold;
    int _HotTreshold;
    

public:
    DHTEntity()  : Entity(){}

    DHTEntity(int id, int ModuleId, String Type, int PinNumber, int DryTreshold, int WetTreshold, int CoolTreshold, int HotTreshold) : Entity() {
        this->id = id;
        _ModuleId = ModuleId;
        _Type = Type;
        _PinNumber = PinNumber;
        _DryTreshold = DryTreshold;
        _WetTreshold = WetTreshold;
        _CoolTreshold = CoolTreshold;
        _HotTreshold = HotTreshold;
        

        addColumn(COLUMN_MODULEID, String(ModuleId), "int");
        addColumn(COLUMN_TYPE, String(Type), "String");
        addColumn(COLUMN_PINNUMBER, String(PinNumber), "int");
        addColumn(COLUMN_DRYTRESHOLD, String(DryTreshold), "int");
        addColumn(COLUMN_WETTRESHOLD, String(WetTreshold), "int");
        addColumn(COLUMN_COOLTRESHOLD, String(CoolTreshold), "int");
        addColumn(COLUMN_HOTTRESHOLD, String(HotTreshold), "int");
        
    }

    DHTEntity(int ModuleId, String Type, int PinNumber, int DryTreshold, int WetTreshold, int CoolTreshold, int HotTreshold) : 
        DHTEntity(0, _ModuleId, _Type, _PinNumber, _DryTreshold, _WetTreshold, _CoolTreshold, _HotTreshold)  {}

    static DHTEntity fromEntity(Entity entity)
    {
        DHTEntity dhtentity = DHTEntity();
        dhtentity.fromString(entity.toString());
        return dhtentity;
    }

    // Getters for each field
    int getModuleId() {
        return _ModuleId;
    }
    String getType() {
        return _Type;
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
    int getCoolTreshold() {
        return _CoolTreshold;
    }
    int getHotTreshold() {
        return _HotTreshold;
    }
    
    
    // Setters for each field
    void setModuleId(int ModuleId) {
        SetValue(COLUMN_MODULEID, String(ModuleId));
        _ModuleId = ModuleId;
    }
    void setType(String Type) {
        SetValue(COLUMN_TYPE, String(Type));
        _Type = Type;
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
    void setCoolTreshold(int CoolTreshold) {
        SetValue(COLUMN_COOLTRESHOLD, String(CoolTreshold));
        _CoolTreshold = CoolTreshold;
    }
    void setHotTreshold(int HotTreshold) {
        SetValue(COLUMN_HOTTRESHOLD, String(HotTreshold));
        _HotTreshold = HotTreshold;
    }
    
};

const String DHTEntity::COLUMN_MODULEID = "ModuleId";
const String DHTEntity::COLUMN_TYPE = "Type";
const String DHTEntity::COLUMN_PINNUMBER = "PinNumber";
const String DHTEntity::COLUMN_DRYTRESHOLD = "DryTreshold";
const String DHTEntity::COLUMN_WETTRESHOLD = "WetTreshold";
const String DHTEntity::COLUMN_COOLTRESHOLD = "CoolTreshold";
const String DHTEntity::COLUMN_HOTTRESHOLD = "HotTreshold";


#endif // DHTENTITY_H