#ifndef BUTTONENTITY_H
#define BUTTONENTITY_H

#include "..\Entity.h"

class ButtonEntity : public Entity {
public:
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_PIN_NUMBER;
    static const String COLUMN_BUTTON_TYPE;
    static const String COLUMN_ACTIVE_HIGH;
    static const String COLUMN_PULLUP_ACTIVE;
    static const String COLUMN_DEBOUNCE_DELAY;

private:
    int ModuleId;
    int PinNumber;
    String ButtonType;
    bool ActiveHigh;
    bool PullupActive;
    int DebounceDelay;

public:
    ButtonEntity() : Entity() {}

    ButtonEntity(int id, int pin_number, int moduleId, const String &_ButtonType, bool activeHigh, bool pullupActive, int debounceDelay) : Entity(id) {
        ModuleId = moduleId;
        PinNumber = pin_number;
        ButtonType = _ButtonType;
        ActiveHigh = activeHigh;
        PullupActive = pullupActive;
        DebounceDelay = debounceDelay;
    }

    ButtonEntity(int pin_number, int moduleId, const String &_ButtonType, bool activeHigh, bool pullupActive, int debounceDelay):
        ButtonEntity(0, pin_number, moduleId, _ButtonType, activeHigh, pullupActive, debounceDelay)
    {

    }

    // Getters
    int getModuleId() {
        ModuleId = GetValue(COLUMN_MODULE_ID).toInt();
        return ModuleId;
    }
    int getPinNumber() {
        PinNumber = GetValue(COLUMN_PIN_NUMBER).toInt();
        return PinNumber;
    }
    String getButtonType() {
        ButtonType = GetValue(COLUMN_BUTTON_TYPE);
        return ButtonType;
    }
    bool getActiveHigh() {
        ActiveHigh = GetValue(COLUMN_ACTIVE_HIGH).toInt() != 0;
        return ActiveHigh;
    }
    bool getPullupActive() {
        PullupActive = GetValue(COLUMN_PULLUP_ACTIVE).toInt() != 0;
        return PullupActive;
    }
    int getDebounceDelay() {
        DebounceDelay = GetValue(COLUMN_DEBOUNCE_DELAY).toInt();
        return DebounceDelay;
    }

    // Setters
    void setModuleId(int moduleId) {
        ModuleId = moduleId;
        SetValue(COLUMN_MODULE_ID, String(ModuleId));
    }
    void setPinNumber(int pin_number) {
        PinNumber = pin_number;
        SetValue(COLUMN_PIN_NUMBER, String(PinNumber));
    }
    void setButtonType(const String &_ButtonType) {
        ButtonType = _ButtonType;
        SetValue(COLUMN_BUTTON_TYPE, ButtonType);
    }
    void setActiveHigh(bool activeHigh) {
        ActiveHigh = activeHigh;
        SetValue(COLUMN_ACTIVE_HIGH, String(ActiveHigh));
    }
    void setPullupActive(bool pullupActive) {
        PullupActive = pullupActive;
        SetValue(COLUMN_PULLUP_ACTIVE, String(PullupActive));
    }
    void setDebounceDelay(int debounceDelay) {
        DebounceDelay = debounceDelay;
        SetValue(COLUMN_DEBOUNCE_DELAY, String(DebounceDelay));
    }

    static ButtonEntity fromEntity(Entity entity)
    {
        ButtonEntity buttonEntity = ButtonEntity();
        buttonEntity.fromString(entity.toString());
        return  buttonEntity;
    }
};

const String ButtonEntity::COLUMN_MODULE_ID = "ModuleId";
const String ButtonEntity::COLUMN_PIN_NUMBER = "PinNumber";
const String ButtonEntity::COLUMN_BUTTON_TYPE = "ButtonType";
const String ButtonEntity::COLUMN_ACTIVE_HIGH = "ActiveHigh";
const String ButtonEntity::COLUMN_PULLUP_ACTIVE = "PullupActive";
const String ButtonEntity::COLUMN_DEBOUNCE_DELAY = "DebounceDelay";

#endif // BUTTONENTITY_H
