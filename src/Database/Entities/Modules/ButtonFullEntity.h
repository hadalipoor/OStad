#ifndef BUTTONFULLENTITY_H
#define BUTTONFULLENTITY_H


class ButtonFullEntity {
public:
    int Id;
    int ModuleId;
    String Name;
    int DeviceId;
    int ServerId;
    int PinNumber;
    String ButtonType;
    bool ActiveHigh;
    bool PullupActive;
    int DebounceDelay;
    int longPressTime;


    ButtonFullEntity(int id, int moduleId, String name, int pinNumber, String buttonType,
                     bool activeHigh, bool pullupActive, int debounceDelay, int deviceId, int serverId)  {
        Id = id;
        ButtonType = buttonType;
        ActiveHigh = activeHigh;
        PullupActive = pullupActive;
        DebounceDelay = debounceDelay;
        ModuleId = moduleId;
        Name = name;
        DeviceId = deviceId;
        ServerId = serverId;
        PinNumber = pinNumber;
    }
    
    ButtonFullEntity(): ButtonFullEntity(0, 0, "", 0, "", false, false, 0, 0, 0) {}
};
#endif // BUTTONFULLENTITY_H
