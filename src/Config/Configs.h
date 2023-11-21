#ifndef CONFIGS_H
#define CONFIGS_H

#include "IConfigs.h"
#include "System/SystemConfig.h"
#include "Security/SecurityConfig.h"
#include "../Context.h"

class Configs : public IConfigs
{
private:
    Context* context;
    SystemConfig* systemConfig;
    SecurityConfig* securityConfig;
    
public:
    Configs(Context* cntxt);
    void initialize();
    IConfig* getSystemConfig() override;
    IConfig* getSecurityConfig() override;
};

Configs::Configs(Context* cntxt) : context(cntxt)
{

}

void Configs::initialize()
{
    securityConfig = new SecurityConfig(context);
    systemConfig = new SystemConfig(context);

    securityConfig->initialize();
    systemConfig->initialize();
}

IConfig* Configs::getSystemConfig()
{
    return systemConfig;
}

IConfig* Configs::getSecurityConfig()
{
    return securityConfig;
}




#endif //CONFIGS_H