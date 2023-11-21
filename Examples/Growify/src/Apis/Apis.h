
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "GreenhousesApis.h"
#include "PlantsApis.h"
#include "LogsApis.h"
#include "ConditionsApis.h"
#include "TemperatureConditionApis.h"
#include "HumidityConditionApis.h"
#include "LightConditionApis.h"
#include "SoilMoistureConditionApis.h"
#include "ConditionApis.h"
#include "GreenhouseApis.h"
#include "PlantTypeApis.h"
#include "PlantApis.h"
#include "GreenhouseSensorApis.h"
#include "GreenhouseControlApis.h"
#include "TemperatureLogApis.h"
#include "HumidityLogApis.h"
#include "LightLogApis.h"
#include "SoilMoistureLogApis.h"


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    GreenhousesApis* greenhousesApis = new GreenhousesApis(appContext, true);
    apis.push_back(greenhousesApis);
    
    PlantsApis* plantsApis = new PlantsApis(appContext, true);
    apis.push_back(plantsApis);
    
    LogsApis* logsApis = new LogsApis(appContext, true);
    apis.push_back(logsApis);
    
    ConditionsApis* conditionsApis = new ConditionsApis(appContext, true);
    apis.push_back(conditionsApis);
    
    TemperatureConditionApis* temperatureconditionApis = new TemperatureConditionApis(appContext, true);
    apis.push_back(temperatureconditionApis);
    
    HumidityConditionApis* humidityconditionApis = new HumidityConditionApis(appContext, true);
    apis.push_back(humidityconditionApis);
    
    LightConditionApis* lightconditionApis = new LightConditionApis(appContext, true);
    apis.push_back(lightconditionApis);
    
    SoilMoistureConditionApis* soilmoistureconditionApis = new SoilMoistureConditionApis(appContext, true);
    apis.push_back(soilmoistureconditionApis);
    
    ConditionApis* conditionApis = new ConditionApis(appContext, true);
    apis.push_back(conditionApis);
    
    GreenhouseApis* greenhouseApis = new GreenhouseApis(appContext, true);
    apis.push_back(greenhouseApis);
    
    PlantTypeApis* planttypeApis = new PlantTypeApis(appContext, true);
    apis.push_back(planttypeApis);
    
    PlantApis* plantApis = new PlantApis(appContext, true);
    apis.push_back(plantApis);
    
    GreenhouseSensorApis* greenhousesensorApis = new GreenhouseSensorApis(appContext, true);
    apis.push_back(greenhousesensorApis);
    
    GreenhouseControlApis* greenhousecontrolApis = new GreenhouseControlApis(appContext, true);
    apis.push_back(greenhousecontrolApis);
    
    TemperatureLogApis* temperaturelogApis = new TemperatureLogApis(appContext, true);
    apis.push_back(temperaturelogApis);
    
    HumidityLogApis* humiditylogApis = new HumidityLogApis(appContext, true);
    apis.push_back(humiditylogApis);
    
    LightLogApis* lightlogApis = new LightLogApis(appContext, true);
    apis.push_back(lightlogApis);
    
    SoilMoistureLogApis* soilmoisturelogApis = new SoilMoistureLogApis(appContext, true);
    apis.push_back(soilmoisturelogApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    