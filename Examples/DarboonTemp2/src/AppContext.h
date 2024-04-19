#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "DarboonTemp2/IDarboonTemp2.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* darboontemp2Config;
    IDarboonTemp2* darboontemp2;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getDarboonTemp2Config() { return darboontemp2Config; }
    void setDarboonTemp2Config(IConfig* config) { darboontemp2Config = config; }
    
    IDarboonTemp2* getDarboonTemp2() { return darboontemp2; }
    void setdarboontemp2(IDarboonTemp2* _darboontemp2) { darboontemp2 = _darboontemp2; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H
