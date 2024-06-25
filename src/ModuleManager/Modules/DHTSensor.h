#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include <DHT.h>
#include "../../Context.h"
#include "../../Database/Entities/Modules/DHTFullEntity.h"
#include "../../Config/Device/DeviceConfigKeys.h"
#include "../../Database/Controllers/Modules/DevicesController.h"
#include "../../Database/Controllers/Modules/ModulesController.h"
#include "IDHTSensor.h"
#include "ModuleTypes.h"

enum class DHTType { DHT11, DHT22 };
enum class DHTFunctions { GET_HUMIDITY, GET_TEMPERATURE_C, GET_TEMPERATURE_F, IS_DATA_VALID };
class DHTSensor: public IDHTSensor {
private:
    Context*  context;
    DHT* dht;
    int pin_number;
    DHTType sensorType;
    float humidity;
    float temperatureC;
    float temperatureF;
    bool dataValid;
    String ip;
    String protocolType;
    String callDHTApi(DHTFunctions function, String data);

public:
    DHTSensor(Context* context, String name, int pin_number, DHTType type);
    DHTSensor(Context* context, String name, int pin_number, DHTType type,int module_id, int device_id, int server_id);
    DHTSensor(Context* context, String name, int pin_number, String type,int module_id, int device_id, int server_id);
    void update() override;
    String getName() override;
    float getHumidity() override;
    float getTemperatureC() override;
    float getTemperatureF() override;
    bool isDataValid() override;
    int getPinNumber() override;
    String getType() override;
    DHTFullEntity* getEntity() override;
};

DHTSensor::DHTSensor(Context* context, String name, int pin_number, DHTType type,int module_id, int device_id, int server_id) : 
    IDHTSensor(module_id, server_id, name, ModuleTypes::DHT, device_id), context(context), pin_number(pin_number), sensorType(type), humidity(0.0), temperatureC(0.0), temperatureF(0.0), dataValid(false) {
    int dhtType = (sensorType == DHTType::DHT11) ? DHT11 : DHT22;
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        dht = new DHT(pin_number, dhtType);
    }
    else
    {
        protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
        ModulesController* modulesController = new ModulesController(context, storageType);
        DHTFullEntity* dhtEntity = modulesController->getDHTByServerId(server_id);
        int deviceId = dhtEntity->DeviceId;
        DevicesController* devicesController = new DevicesController(context, storageType);
        DevicesEntity device = devicesController->GetById(deviceId);
        ip = device.getIP();
    }
}
DHTSensor::DHTSensor(Context* context, String name, int pin_number, String type,int module_id, int device_id, int server_id) : 
    DHTSensor(context, name, pin_number, type == "DHT11"? DHTType::DHT11: DHTType::DHT22, module_id, device_id, server_id)
{
    
}

DHTSensor::DHTSensor(Context* context, String name, int pin_number, DHTType type)
    : DHTSensor(context, name, pin_number, type, 0, 0, 0)
{
    
}

String DHTSensor::callDHTApi(DHTFunctions function, String data)
{
    String functionStr = "";
    switch(function)
    {
        case DHTFunctions::GET_HUMIDITY :
            functionStr = "get_humidity";
            break;
        case DHTFunctions::GET_TEMPERATURE_C :
            functionStr = "get_temperature_c";
            break;
        case DHTFunctions::GET_TEMPERATURE_F :
            functionStr = "get_temperature_f";
            break;
    }
    String endpoint = protocolType + "://" + ip + "/dhtsensorcontroller/"+ functionStr;
    return context->getNetwork()->getApiManager()->makePostRequest(endpoint, data);

}

void DHTSensor::update() {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        humidity = dht->readHumidity();
        temperatureC = dht->readTemperature();
        temperatureF = dht->readTemperature(true);
        dataValid = !isnan(humidity) && !isnan(temperatureC);
    }
}

String DHTSensor::getName(){
    return _name;
}

float DHTSensor::getHumidity() {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        return humidity;
    }
    else
    {
        callDHTApi(DHTFunctions::GET_HUMIDITY, "{\"server_id\":"+String(getServerId()) + "}");
    }
}

float DHTSensor::getTemperatureC() {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        return temperatureC;
    }
    else
    {
        callDHTApi(DHTFunctions::GET_TEMPERATURE_C, "{\"server_id\":"+String(getServerId()) + "}");
    }
}

float DHTSensor::getTemperatureF() {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        return temperatureF;
    }
    else
    {
        callDHTApi(DHTFunctions::GET_TEMPERATURE_F, "{\"server_id\":"+String(getServerId()) + "}");
    }

}

bool DHTSensor::isDataValid() {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        return dataValid;
    }
    else
    {
        callDHTApi(DHTFunctions::IS_DATA_VALID, "{\"server_id\":"+String(getServerId()) + "}");
    }

}

int DHTSensor::getPinNumber()
{
    return pin_number;
}

String DHTSensor::getType()
{
    return sensorType == DHTType::DHT11? "DHT11": "DHT22";
}
DHTFullEntity* DHTSensor::getEntity() {
    return new DHTFullEntity(0, 0, _name, pin_number, sensorType == DHTType::DHT11 ? "DHT11" : "DHT22", 0, 0, 0, 0, 0, getServerId());
}

#endif // DHT_H
