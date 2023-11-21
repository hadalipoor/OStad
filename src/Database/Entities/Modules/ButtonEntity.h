#ifndef BUTTONENTITY_H
#define BUTTONENTITY_H

#include "..\Entity.h"

class ButtonEntity : public Entity {
public:
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_BUTTON_TYPE;
    static const String COLUMN_ACTIVE_HIGH;
    static const String COLUMN_PULLUP_ACTIVE;
    static const String COLUMN_DEBOUNCE_DELAY;

    int ModuleId;
    String ButtonType;
    bool ActiveHigh;
    bool PullupActive;
    int DebounceDelay;

    ButtonEntity()  : Entity(){}

    ButtonEntity(int id, int moduleId, const String &_ButtonType, bool activeHigh, bool pullupActive, int debounceDelay) : Entity() {
        this->id = id;
        ModuleId = moduleId;
        ButtonType = _ButtonType;
        ActiveHigh = activeHigh;
        PullupActive = pullupActive;
        DebounceDelay = debounceDelay;
        addColumn(COLUMN_MODULE_ID, String(ModuleId), "int");
        addColumn(COLUMN_BUTTON_TYPE, ButtonType, "string");
        addColumn(COLUMN_ACTIVE_HIGH, String(ActiveHigh), "bool");
        addColumn(COLUMN_PULLUP_ACTIVE, String(PullupActive), "bool");
        addColumn(COLUMN_DEBOUNCE_DELAY, String(DebounceDelay), "int");
    }

    ButtonEntity(int moduleId, const String &_ButtonType, bool activeHigh, bool pullupActive, int debounceDelay) : 
        ButtonEntity(0, moduleId, _ButtonType, activeHigh, pullupActive, debounceDelay)  {}

    static ButtonEntity fromEntity(Entity entity)
    {
        ButtonEntity buttonEntity = ButtonEntity();
        buttonEntity.fromString(entity.toString());
        return buttonEntity;
    }

    // Setters and Getters for each field
};

const String ButtonEntity::COLUMN_MODULE_ID = "ModuleId";
const String ButtonEntity::COLUMN_BUTTON_TYPE = "ButtonType";
const String ButtonEntity::COLUMN_ACTIVE_HIGH = "ActiveHigh";
const String ButtonEntity::COLUMN_PULLUP_ACTIVE = "PullupActive";
const String ButtonEntity::COLUMN_DEBOUNCE_DELAY = "DebounceDelay";

#endif // BUTTONENTITY_H
