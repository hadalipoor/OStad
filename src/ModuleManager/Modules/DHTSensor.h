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

class DHTSensor: public IDHTSensor {
private:
    Context*  context;
    DHT* dht;
    String _name;
    int pin_number;
    DHTType sensorType;
    float humidity;
    float temperatureC;
    float temperatureF;
    bool dataValid;
    int serverId;
    String ip;
    String protocolType;

public:
    DHTSensor(Context* context, String name, int pin_number, DHTType type);
    DHTSensor(Context* context, String name, int pin_number, DHTType type, int server_id);
    void update() override;
    String getName() override;
    float getHumidity() override;
    float getTemperatureC() override;
    float getTemperatureF() override;
    bool isDataValid() override;
    DHTFullEntity* getEntity() override;
    int getServerId() override;
    void setServerId(int serverId) override;
};

DHTSensor::DHTSensor(Context* context, String name, int pin_number, DHTType type, int server_id) : context(context), _name(name), pin_number(pin_number), sensorType(type), humidity(0.0), temperatureC(0.0), temperatureF(0.0), dataValid(false), serverId(server_id) {
    int dhtType = (sensorType == DHTType::DHT11) ? DHT11 : DHT22;
    dht = new DHT(pin_number, dhtType);
    protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
    ModulesController* modulesController = new ModulesController(context, storageType);
    DHTFullEntity dhtEntity = modulesController->getRelayByServerId(server_id);
    int deviceId = dhtEntity.DeviceId;
    DevicesController* devicesController = new DevicesController(context, storageType);
    DevicesEntity device = devicesController->GetById(deviceId);
    ip = device.getIP();

}

DHTSensor::DHTSensor(Context* context, String name, int pin_number, DHTType type)
    : DHTSensor(context, name, pin_number, type, 0)
{

}

void DHTSensor::update() {
    humidity = dht->readHumidity();
    temperatureC = dht->readTemperature();
    temperatureF = dht->readTemperature(true);
    dataValid = !isnan(humidity) && !isnan(temperatureC);
}

String DHTSensor::getName(){
    return _name;
}

float DHTSensor::getHumidity() {
    return humidity;
}

float DHTSensor::getTemperatureC() {
    return temperatureC;
}

float DHTSensor::getTemperatureF() {
    return temperatureF;
}

bool DHTSensor::isDataValid() {
    return dataValid;
}

DHTFullEntity* DHTSensor::getEntity() {
    return new DHTFullEntity(0, 0, "DHT Sensor", ModuleTypes::DHT, "", 0, pin_number, sensorType == DHTType::DHT11 ? "DHT11" : "DHT22", 0, 0, 0, 0);
}

#endif // DHT_H
