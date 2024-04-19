#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "SabooraHub2/ISabooraHub2.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* saboorahub2Config;
    ISabooraHub2* saboorahub2;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getSabooraHub2Config() { return saboorahub2Config; }
    void setSabooraHub2Config(IConfig* config) { saboorahub2Config = config; }
    
    ISabooraHub2* getSabooraHub2() { return saboorahub2; }
    void setsaboorahub2(ISabooraHub2* _saboorahub2) { saboorahub2 = _saboorahub2; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H
