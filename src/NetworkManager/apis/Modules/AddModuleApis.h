
#ifndef ADDMODULEAPIS_H
#define ADDMODULEAPIS_H

#include "ModulePermissions.h"
#include "RelayControllerApis.h"
#include "ButtonControllerApis.h"
#include "DHTSensorControllerApis.h"
#include "LCD16x2ControllerApis.h"
#include "OLEDLCDControllerApis.h"
#include "SoilMoistureSensorControllerApis.h"
#include "ButtonApis.h"
#include "ModuleApis.h"
#include "RelayApis.h"
#include "LCDApis.h"
#include "DHTApis.h"
#include "PhotoresistorApis.h"
#include "RGBApis.h"
#include "SoilMoistureApis.h"
#include "RFIDApis.h"
#include "DevicesApis.h"


void createModulesApis(Context* context)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    RelayControllerApis* relaycontrollerApis = new RelayControllerApis(context, true);
    apis.push_back(relaycontrollerApis);
    
    ButtonControllerApis* buttoncontrollerApis = new ButtonControllerApis(context, true);
    apis.push_back(buttoncontrollerApis);
    
    DHTSensorControllerApis* dhtsensorcontrollerApis = new DHTSensorControllerApis(context, true);
    apis.push_back(dhtsensorcontrollerApis);
    
    LCD16x2ControllerApis* lcd16x2controllerApis = new LCD16x2ControllerApis(context, true);
    apis.push_back(lcd16x2controllerApis);
    
    OLEDLCDControllerApis* oledlcdcontrollerApis = new OLEDLCDControllerApis(context, true);
    apis.push_back(oledlcdcontrollerApis);
    
    SoilMoistureSensorControllerApis* soilmoisturesensorcontrollerApis = new SoilMoistureSensorControllerApis(context, true);
    apis.push_back(soilmoisturesensorcontrollerApis);
    
    ButtonApis* buttonApis = new ButtonApis(context, true);
    apis.push_back(buttonApis);
    
    ModuleApis* moduleApis = new ModuleApis(context, true);
    apis.push_back(moduleApis);
    
    RelayApis* relayApis = new RelayApis(context, true);
    apis.push_back(relayApis);
    
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
    
    RFIDApis* rfidApis = new RFIDApis(context, true);
    apis.push_back(rfidApis);
    
    DevicesApis* devicesApis = new DevicesApis(context, true);
    apis.push_back(devicesApis);
    

    context->getNetwork()->addApis(apis);
}

#endif //ADDMODULEAPIS_H
    