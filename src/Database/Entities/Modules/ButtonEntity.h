#ifndef BUTTONENTITY_H
#define BUTTONENTITY_H

#include "../Entity.h"

class ButtonEntity : public Entity {
public:
    static const String COLUMN_MODULEID;
    static const String COLUMN_BUTTONTYPE;
    static const String COLUMN_PINNUMBER;
    static const String COLUMN_ACTIVEHIGH;
    static const String COLUMN_PULLUPACTIVE;
    static const String COLUMN_DEBOUNCEDELAY;
    
private:
    int _ModuleId;
    String _ButtonType;
    int _PinNumber;
    bool _ActiveHigh;
    bool _PullupActive;
    int _DebounceDelay;
    

public:
    ButtonEntity()  : Entity(){}

    ButtonEntity(int id, int ModuleId, String ButtonType, int PinNumber, bool ActiveHigh, bool PullupActive, int DebounceDelay) : Entity() {
        this->id = id;
        _ModuleId = ModuleId;
        _ButtonType = ButtonType;
        _PinNumber = PinNumber;
        _ActiveHigh = ActiveHigh;
        _PullupActive = PullupActive;
        _DebounceDelay = DebounceDelay;
        

        addColumn(COLUMN_MODULEID, String(ModuleId), "int");
        addColumn(COLUMN_BUTTONTYPE, String(ButtonType), "String");
        addColumn(COLUMN_PINNUMBER, String(PinNumber), "int");
        addColumn(COLUMN_ACTIVEHIGH, String(ActiveHigh), "bool");
        addColumn(COLUMN_PULLUPACTIVE, String(PullupActive), "bool");
        addColumn(COLUMN_DEBOUNCEDELAY, String(DebounceDelay), "int");
        
    }

    ButtonEntity(int ModuleId, String ButtonType, int PinNumber, bool ActiveHigh, bool PullupActive, int DebounceDelay) : 
        ButtonEntity(0, _ModuleId, _ButtonType, _PinNumber, _ActiveHigh, _PullupActive, _DebounceDelay)  {}

    static ButtonEntity fromEntity(Entity entity)
    {
        ButtonEntity buttonentity = ButtonEntity();
        buttonentity.fromString(entity.toString());
        return buttonentity;
    }

    // Getters for each field
    int getModuleId() {
        return _ModuleId;
    }
    String getButtonType() {
        return _ButtonType;
    }
    int getPinNumber() {
        return _PinNumber;
    }
    bool getActiveHigh() {
        return _ActiveHigh;
    }
    bool getPullupActive() {
        return _PullupActive;
    }
    int getDebounceDelay() {
        return _DebounceDelay;
    }
    
    
    // Setters for each field
    void setModuleId(int ModuleId) {
        SetValue(COLUMN_MODULEID, String(ModuleId));
        _ModuleId = ModuleId;
    }
    void setButtonType(String ButtonType) {
        SetValue(COLUMN_BUTTONTYPE, String(ButtonType));
        _ButtonType = ButtonType;
    }
    void setPinNumber(int PinNumber) {
        SetValue(COLUMN_PINNUMBER, String(PinNumber));
        _PinNumber = PinNumber;
    }
    void setActiveHigh(bool ActiveHigh) {
        SetValue(COLUMN_ACTIVEHIGH, String(ActiveHigh));
        _ActiveHigh = ActiveHigh;
    }
    void setPullupActive(bool PullupActive) {
        SetValue(COLUMN_PULLUPACTIVE, String(PullupActive));
        _PullupActive = PullupActive;
    }
    void setDebounceDelay(int DebounceDelay) {
        SetValue(COLUMN_DEBOUNCEDELAY, String(DebounceDelay));
        _DebounceDelay = DebounceDelay;
    }
    
};

const String ButtonEntity::COLUMN_MODULEID = "ModuleId";
const String ButtonEntity::COLUMN_BUTTONTYPE = "ButtonType";
const String ButtonEntity::COLUMN_PINNUMBER = "PinNumber";
const String ButtonEntity::COLUMN_ACTIVEHIGH = "ActiveHigh";
const String ButtonEntity::COLUMN_PULLUPACTIVE = "PullupActive";
const String ButtonEntity::COLUMN_DEBOUNCEDELAY = "DebounceDelay";


#endif // BUTTONENTITY_H