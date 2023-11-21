
#ifndef ADDSYSTEMAPIS_H
#define ADDSYSTEMAPIS_H

#include "SystemPermissions.h"
#include "ClockApis.h"
#include "FileApis.h"
#include "LogApis.h"
#include "SSIDApis.h"
#include "SystemConfigApis.h"
#include "WiFiApis.h"


void createSystemApis(Context* context)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    ClockApis*  clockApis= new ClockApis(context, true);
    apis.push_back(clockApis);
    
    FileApis*  fileApis= new FileApis(context, true);
    apis.push_back(fileApis);
    
    LogApis* logApis = new LogApis(context, true);
    apis.push_back(logApis);
    
    SSIDApis*  sSIDApis= new SSIDApis(context, true);
    apis.push_back(sSIDApis);
    
    SystemConfigAPis*  systemConfigAPis= new SystemConfigAPis(context, true);
    apis.push_back(systemConfigAPis);
    
    WiFiApis* wiFiApis = new WiFiApis(context, true);
    apis.push_back(wiFiApis);

    context->getNetwork()->addApis(apis);
}

#endif //APIS_H
    