#ifndef BUTTONFULLENTITY_H
#define BUTTONFULLENTITY_H


class ButtonFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber;
    String ButtonType;
    bool ActiveHigh;
    bool PullupActive;
    int DebounceDelay;
    int longPressTime;

    ButtonFullEntity() {}

    ButtonFullEntity(int id, int moduleId, String _Name, String _ModuleType, String _ConnectionType, int nodeId,
                     int pinNumber, String _ButtonType, bool activeHigh, bool pullupActive, int debounceDelay)  {
        this->id = id;
        ButtonType = _ButtonType;
        ActiveHigh = activeHigh;
        PullupActive = pullupActive;
        DebounceDelay = debounceDelay;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber = pinNumber;

    }

};
#endif // BUTTONFULLENTITY_H
