#ifndef ICONFIG_H
#define ICONFIG_H

#include "IConfig.h"

class IConfigs
{
public:
    virtual void initialize() = 0;
    virtual IConfig* getSystemConfig() = 0;
    virtual IConfig* getSecurityConfig() = 0;
};


#endif //ICONFIG_H