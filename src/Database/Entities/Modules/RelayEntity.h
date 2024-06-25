#ifndef RELAYENTITY_H
#define RELAYENTITY_H

#include "../Entity.h"

class RelayEntity : public Entity {
public:
    static const String COLUMN_MODULEID;
    static const String COLUMN_PINNUMBER;
    static const String COLUMN_NORMALLYOPEN;
    
private:
    int _ModuleId;
    int _PinNumber;
    bool _NormallyOpen;
    

public:
    RelayEntity()  : Entity(){}

    RelayEntity(int id, int ModuleId, int PinNumber, bool NormallyOpen) : Entity() {
        this->id = id;
        _ModuleId = ModuleId;
        _PinNumber = PinNumber;
        _NormallyOpen = NormallyOpen;
        

        addColumn(COLUMN_MODULEID, String(ModuleId), "int");
        addColumn(COLUMN_PINNUMBER, String(PinNumber), "int");
        addColumn(COLUMN_NORMALLYOPEN, String(NormallyOpen), "bool");
        
    }

    RelayEntity(int ModuleId, int PinNumber, bool NormallyOpen) : 
        RelayEntity(0, _ModuleId, _PinNumber, _NormallyOpen)  {}

    static RelayEntity fromEntity(Entity entity)
    {
        RelayEntity relayentity = RelayEntity();
        relayentity.fromString(entity.toString());
        return relayentity;
    }

    // Getters for each field
    int getModuleId() {
        return _ModuleId;
    }
    int getPinNumber() {
        return _PinNumber;
    }
    bool getNormallyOpen() {
        return _NormallyOpen;
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
    void setNormallyOpen(bool NormallyOpen) {
        SetValue(COLUMN_NORMALLYOPEN, String(NormallyOpen));
        _NormallyOpen = NormallyOpen;
    }
    
};

const String RelayEntity::COLUMN_MODULEID = "ModuleId";
const String RelayEntity::COLUMN_PINNUMBER = "PinNumber";
const String RelayEntity::COLUMN_NORMALLYOPEN = "NormallyOpen";


#endif // RELAYENTITY_H