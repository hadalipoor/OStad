#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "Authentication/IAuthentication.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* authenticationConfig;
    IAuthentication* authentication;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getAuthenticationConfig() { return authenticationConfig; }
    void setAuthenticationConfig(IConfig* config) { authenticationConfig = config; }
    
    IAuthentication* getAuthentication() { return authentication; }
    void setauthentication(IAuthentication* _authentication) { authentication = _authentication; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H
