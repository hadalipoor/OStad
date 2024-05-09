
#ifndef ADDMODULESAPIS_H
#define ADDMODULESAPIS_H

#include "ModulePermissions.h"
#include "ButtonApis.h"
#include "ModuleApis.h"
#include "RelayApis.h"
#include "RelayControllerApis.h"
#include "LCDApis.h"
#include "DHTApis.h"
#include "PhotoresistorApis.h"
#include "RGBApis.h"
#include "SoilMoistureApis.h"


void createModulesApis(Context* context)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    ButtonApis* buttonApis = new ButtonApis(context, true);
    apis.push_back(buttonApis);
    
    ModuleApis* moduleApis = new ModuleApis(context, true);
    apis.push_back(moduleApis);
    
    RelayApis* relayApis = new RelayApis(context, true);
    apis.push_back(relayApis);
    
    RelayControllerApis* relayControllerApis = new RelayControllerApis(context, true);
    apis.push_back(relayControllerApis);

    LCDApis* lcdApis = new LCDApis(context, true);
    apis.push_back(lcdApis);
    
    DHTApis* dhtApis = new DHTApis(context, true);
    apis.push_back(dhtApis);
    
    PhotoresistorApis* photoresistorApis = new PhotoresistorApis(context, true);
    apis.push_back(photoresistorApis);
    
    RGBApis* rgbApis = new RGBApis(context, true);
    apis.push_back(rgbApis);
    
    SoilMoistureApis* soilmoistureApis = new SoilMoistureApis(context, true);
    apis.push_back(soilmoistureApis);
    

    context->getNetwork()->addApis(apis);
}

#endif //APIS_H
    