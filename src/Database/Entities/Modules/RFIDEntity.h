#ifndef RFIDENTITY_H
#define RFIDENTITY_H

#include "../Entity.h"

class RFIDEntity : public Entity {
public:
    static const String COLUMN_MODULEID;
    static const String COLUMN_PINNUMBER1;
    static const String COLUMN_PINNUMBER2;
    
private:
    int _ModuleId;
    int _PinNumber1;
    int _PinNumber2;
    

public:
    RFIDEntity()  : Entity(){}

    RFIDEntity(int id, int ModuleId, int PinNumber1, int PinNumber2) : Entity() {
        this->id = id;
        _ModuleId = ModuleId;
        _PinNumber1 = PinNumber1;
        _PinNumber2 = PinNumber2;
        

        addColumn(COLUMN_MODULEID, String(ModuleId), "int");
        addColumn(COLUMN_PINNUMBER1, String(PinNumber1), "int");
        addColumn(COLUMN_PINNUMBER2, String(PinNumber2), "int");
        
    }

    RFIDEntity(int ModuleId, int PinNumber1, int PinNumber2) : 
        RFIDEntity(0, _ModuleId, _PinNumber1, _PinNumber2)  {}

    static RFIDEntity fromEntity(Entity entity)
    {
        RFIDEntity rfidentity = RFIDEntity();
        rfidentity.fromString(entity.toString());
        return rfidentity;
    }

    // Getters for each field
    int getModuleId() {
        return _ModuleId;
    }
    int getPinNumber1() {
        return _PinNumber1;
    }
    int getPinNumber2() {
        return _PinNumber2;
    }
    
    
    // Setters for each field
    void setModuleId(int ModuleId) {
        SetValue(COLUMN_MODULEID, String(ModuleId));
        _ModuleId = ModuleId;
    }
    void setPinNumber1(int PinNumber1) {
        SetValue(COLUMN_PINNUMBER1, String(PinNumber1));
        _PinNumber1 = PinNumber1;
    }
    void setPinNumber2(int PinNumber2) {
        SetValue(COLUMN_PINNUMBER2, String(PinNumber2));
        _PinNumber2 = PinNumber2;
    }
    
};

const String RFIDEntity::COLUMN_MODULEID = "ModuleId";
const String RFIDEntity::COLUMN_PINNUMBER1 = "PinNumber1";
const String RFIDEntity::COLUMN_PINNUMBER2 = "PinNumber2";


#endif // RFIDENTITY_H