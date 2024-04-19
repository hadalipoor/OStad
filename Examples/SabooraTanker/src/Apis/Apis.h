
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "TankerApis.h"


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    TankerApis* tankerApis = new TankerApis(appContext, true);
    apis.push_back(tankerApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    