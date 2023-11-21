
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "PrinterApis.h"
#include "TemplatesApis.h"
#include "RecentActivitiesApis.h"


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    PrinterApis* printerApis = new PrinterApis(appContext, true);
    apis.push_back(printerApis);
    
    TemplatesApis* templatesApis = new TemplatesApis(appContext, true);
    apis.push_back(templatesApis);
    
    RecentActivitiesApis* recentactivitiesApis = new RecentActivitiesApis(appContext, true);
    apis.push_back(recentactivitiesApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    