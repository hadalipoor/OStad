#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "SabooraTanker/ISabooraTanker.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* sabooratankerConfig;
    ISabooraTanker* sabooratanker;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getSabooraTankerConfig() { return sabooratankerConfig; }
    void setSabooraTankerConfig(IConfig* config) { sabooratankerConfig = config; }
    
    ISabooraTanker* getSabooraTanker() { return sabooratanker; }
    void setsabooratanker(ISabooraTanker* _sabooratanker) { sabooratanker = _sabooratanker; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H
