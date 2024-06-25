#ifndef PHOTORESISTORENTITY_H
#define PHOTORESISTORENTITY_H

#include "../Entity.h"

class PhotoresistorEntity : public Entity {
public:
    static const String COLUMN_MODULEID;
    static const String COLUMN_PINNUMBER;
    static const String COLUMN_LOWTRESHOLD;
    static const String COLUMN_HIGHTRESHOLD;
    
private:
    int _ModuleId;
    int _PinNumber;
    int _LowTreshold;
    int _HighTreshold;
    

public:
    PhotoresistorEntity()  : Entity(){}

    PhotoresistorEntity(int id, int ModuleId, int PinNumber, int LowTreshold, int HighTreshold) : Entity() {
        this->id = id;
        _ModuleId = ModuleId;
        _PinNumber = PinNumber;
        _LowTreshold = LowTreshold;
        _HighTreshold = HighTreshold;
        

        addColumn(COLUMN_MODULEID, String(ModuleId), "int");
        addColumn(COLUMN_PINNUMBER, String(PinNumber), "int");
        addColumn(COLUMN_LOWTRESHOLD, String(LowTreshold), "int");
        addColumn(COLUMN_HIGHTRESHOLD, String(HighTreshold), "int");
        
    }

    PhotoresistorEntity(int ModuleId, int PinNumber, int LowTreshold, int HighTreshold) : 
        PhotoresistorEntity(0, _ModuleId, _PinNumber, _LowTreshold, _HighTreshold)  {}

    static PhotoresistorEntity fromEntity(Entity entity)
    {
        PhotoresistorEntity photoresistorentity = PhotoresistorEntity();
        photoresistorentity.fromString(entity.toString());
        return photoresistorentity;
    }

    // Getters for each field
    int getModuleId() {
        return _ModuleId;
    }
    int getPinNumber() {
        return _PinNumber;
    }
    int getLowTreshold() {
        return _LowTreshold;
    }
    int getHighTreshold() {
        return _HighTreshold;
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
    void setLowTreshold(int LowTreshold) {
        SetValue(COLUMN_LOWTRESHOLD, String(LowTreshold));
        _LowTreshold = LowTreshold;
    }
    void setHighTreshold(int HighTreshold) {
        SetValue(COLUMN_HIGHTRESHOLD, String(HighTreshold));
        _HighTreshold = HighTreshold;
    }
    
};

const String PhotoresistorEntity::COLUMN_MODULEID = "ModuleId";
const String PhotoresistorEntity::COLUMN_PINNUMBER = "PinNumber";
const String PhotoresistorEntity::COLUMN_LOWTRESHOLD = "LowTreshold";
const String PhotoresistorEntity::COLUMN_HIGHTRESHOLD = "HighTreshold";


#endif // PHOTORESISTORENTITY_H