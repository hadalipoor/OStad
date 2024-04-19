#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "Darboon/IDarboon.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* darboonConfig;
    IDarboon* darboon;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getDarboonConfig() { return darboonConfig; }
    void setDarboonConfig(IConfig* config) { darboonConfig = config; }
    
    IDarboon* getDarboon() { return darboon; }
    void setdarboon(IDarboon* _darboon) { darboon = _darboon; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H
