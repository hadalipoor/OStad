
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "RelayManagerApis.h"


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    RelayManagerApis* relaymanagerApis = new RelayManagerApis(appContext, true);
    apis.push_back(relaymanagerApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    