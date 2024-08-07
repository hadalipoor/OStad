#ifndef SOILMOISTURE_H
#define SOILMOISTURE_H

#include <Arduino.h>
#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/SoilMoistureFullEntity.h"
#include "ISoilMoistureSensor.h"
#include "../../Context.h"

enum SoilMoistureFunctions{READ_MOISTURE, IS_DRY, IS_WET};
class SoilMoistureSensor: public ISoilMoistureSensor {
private:
    Context* context;
    int sensorPin;       // Pin connected to the soil moisture sensor
    int dryThreshold;    // Threshold value indicating dry soil
    int wetThreshold;    // Threshold value indicating wet soil
    String ip;
    String protocolType;
    void initialize();
    String callSoilMoistureSensorApi(SoilMoistureFunctions function, String data);


public:
    SoilMoistureSensor(Context* context, int sensorPin, int dryThreshold, int wetThreshold, int module_id, int server_id, String name, int device_id);
    
    int readMoisture();
    bool isDry();
    bool isWet();

    int getSensorPin();
    int getDryThreshold();
    int getWetThreshold();

    SoilMoistureFullEntity* getEntity();
};


SoilMoistureSensor::SoilMoistureSensor(Context* context, int sensorPin, int dryThreshold, int wetThreshold, int module_id, int server_id, String name, int device_id)
    : ISoilMoistureSensor(module_id, server_id, name, ModuleTypes::SOILMOISTURE, device_id) ,sensorPin(sensorPin), dryThreshold(dryThreshold), wetThreshold(wetThreshold), context(context) 
{
    if(device_id == context->getDeviceManager()->deviceId)
    {
        initialize();
    }
    else
    {
        protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
        ModulesController* modulesController = new ModulesController(context, storageType);
        SoilMoistureFullEntity* soilMoistureEntity = modulesController->getSoilMoistureByServerId(server_id);
        int deviceId = soilMoistureEntity->DeviceId;
        DevicesController* devicesController = new DevicesController(context, storageType);
        DevicesEntity device = devicesController->GetById(deviceId);
        ip = device.getIP();
    }
}

String SoilMoistureSensor::callSoilMoistureSensorApi(SoilMoistureFunctions function, String data)
{
    String functionStr = "";
    switch(function)
    {
        case READ_MOISTURE:
            functionStr = "read_moisture";
            break;
        case IS_WET:
            functionStr = "is_wet";
            break;
        case IS_DRY:
            functionStr = "is_dry";
            break;
        default:
            functionStr = "read_moisture";
    }

    String endpoint = protocolType + "://" + ip + "/soilmoisturesensorcontroller/"+ functionStr;
    return context->getNetwork()->getApiManager()->makePostRequest(endpoint, data);
}

void SoilMoistureSensor::initialize() {
    pinMode(sensorPin, INPUT);
}

int SoilMoistureSensor::readMoisture() {
    int moisture = analogRead(sensorPin);
    return moisture;
}

bool SoilMoistureSensor::isDry() {
    int moisture = readMoisture();
    return moisture <= dryThreshold;
}

bool SoilMoistureSensor::isWet() {
    int moisture = readMoisture();
    return moisture >= wetThreshold;
}

int SoilMoistureSensor::getSensorPin() {
    return sensorPin;
}

int SoilMoistureSensor::getDryThreshold() {
    return dryThreshold;
}

int SoilMoistureSensor::getWetThreshold() {
    return wetThreshold;
}

SoilMoistureFullEntity* SoilMoistureSensor::getEntity() {
    return new SoilMoistureFullEntity(0, getModuleID(), getName(), getSensorPin(), getDryThreshold(), getWetThreshold(), ModuleTypes::SOILMOISTURE, getDeviceID(), getServerId());
}

#endif // SOILMOISTURE_H
