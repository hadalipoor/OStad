#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "DeviceTest/IDeviceTest.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* devicetestConfig;
    IDeviceTest* devicetest;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getDeviceTestConfig() { return devicetestConfig; }
    void setDeviceTestConfig(IConfig* config) { devicetestConfig = config; }
    
    IDeviceTest* getDeviceTest() { return devicetest; }
    void setdevicetest(IDeviceTest* _devicetest) { devicetest = _devicetest; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H
