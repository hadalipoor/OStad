#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "ElevatorControl/IElevatorControl.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* elevatorcontrolConfig;
    IElevatorControl* elevatorcontrol;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getElevatorControlConfig() { return elevatorcontrolConfig; }
    void setElevatorControlConfig(IConfig* config) { elevatorcontrolConfig = config; }
    
    IElevatorControl* getElevatorControl() { return elevatorcontrol; }
    void setelevatorcontrol(IElevatorControl* _elevatorcontrol) { elevatorcontrol = _elevatorcontrol; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H
