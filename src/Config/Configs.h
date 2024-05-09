#ifndef CONFIGS_H
#define CONFIGS_H

#include "IConfigs.h"
#include "System/SystemConfig.h"
#include "Security/SecurityConfig.h"
#include "Device/DeviceConfig.h"
#include "../Context.h"

class Configs : public IConfigs
{
private:
    Context* context;
    SystemConfig* systemConfig;
    SecurityConfig* securityConfig;
    DeviceConfig* deviceConfig;
    
public:
    Configs(Context* cntxt);
    void initialize();
    IConfig* getSystemConfig() override;
    IConfig* getSecurityConfig() override;
    IConfig* getDeviceConfig() override;
};

Configs::Configs(Context* cntxt) : context(cntxt)
{

}

void Configs::initialize()
{
    securityConfig = new SecurityConfig(context);
    systemConfig = new SystemConfig(context);
    deviceConfig = new DeviceConfig(context);

    securityConfig->initialize();
    systemConfig->initialize();
    deviceConfig->initialize();
}

IConfig* Configs::getSystemConfig()
{
    return systemConfig;
}

IConfig* Configs::getSecurityConfig()
{
    return securityConfig;
}

IConfig* Configs::getDeviceConfig()
{
    return deviceConfig;
}



#endif //CONFIGS_H