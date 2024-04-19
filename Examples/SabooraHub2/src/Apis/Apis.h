
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "LightApis.h"


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    LightApis* lightApis = new LightApis(appContext, true);
    apis.push_back(lightApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    