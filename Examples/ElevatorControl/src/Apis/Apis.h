
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "ElevatorControlApis.h"
#include "FloorApis.h"
#include "ElevatorApis.h"
#include "RequestLogApis.h"
#include "ElevatorLogApis.h"


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    ElevatorControlApis* elevatorcontrolApis = new ElevatorControlApis(appContext, true);
    apis.push_back(elevatorcontrolApis);
    
    FloorApis* floorApis = new FloorApis(appContext, true);
    apis.push_back(floorApis);
    
    ElevatorApis* elevatorApis = new ElevatorApis(appContext, true);
    apis.push_back(elevatorApis);
    
    RequestLogApis* requestlogApis = new RequestLogApis(appContext, true);
    apis.push_back(requestlogApis);
    
    ElevatorLogApis* elevatorlogApis = new ElevatorLogApis(appContext, true);
    apis.push_back(elevatorlogApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    