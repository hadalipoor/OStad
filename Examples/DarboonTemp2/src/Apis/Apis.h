
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "TagControllerApis.h"
#include "GuestsApis.h"
#include "DoorLogApis.h"
#include "DarboonTemp2ConfigApis.h"


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    TagControllerApis* tagcontrollerApis = new TagControllerApis(appContext, true);
    apis.push_back(tagcontrollerApis);
    
    GuestsApis* guestsApis = new GuestsApis(appContext, true);
    apis.push_back(guestsApis);
    
    DoorLogApis* doorlogApis = new DoorLogApis(appContext, true);
    apis.push_back(doorlogApis);
    
    DarboonTemp2ConfigApis* darboontemp2configApis = new DarboonTemp2ConfigApis(appContext, true);
    apis.push_back(darboontemp2configApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    