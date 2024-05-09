#ifndef BUTTONFULLENTITY_H
#define BUTTONFULLENTITY_H


class ButtonFullEntity {
public:
    int Id;
    int ModuleId;
    String Name;
    String ModuleType;
    int DeviceId;
    int PinNumber;
    String ButtonType;
    bool ActiveHigh;
    bool PullupActive;
    int DebounceDelay;
    int longPressTime;

    ButtonFullEntity() {}

    ButtonFullEntity(int id, int moduleId, String name, String moduleType, int deviceId,
                     int pinNumber, String buttonType, bool activeHigh, bool pullupActive, int debounceDelay)  {
        Id = id;
        ButtonType = buttonType;
        ActiveHigh = activeHigh;
        PullupActive = pullupActive;
        DebounceDelay = debounceDelay;
        ModuleId = moduleId;
        Name = name;
        ModuleType = moduleType;
        DeviceId = deviceId;
        PinNumber = pinNumber;
    }
};
#endif // BUTTONFULLENTITY_H
