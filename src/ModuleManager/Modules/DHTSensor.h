#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include <DHT.h>
#include "../../Database/Entities/Modules/DHTFullEntity.h"
#include "ModuleTypes.h"

enum class DHTType { DHT11, DHT22 };

class DHTSensor {
private:
    DHT* dht;
    int pin_number;
    DHTType sensorType;
    float humidity;
    float temperatureC;
    float temperatureF;
    bool dataValid;

public:
    DHTSensor(int pin_number, DHTType type);
    void update();
    float getHumidity() const;
    float getTemperatureC() const;
    float getTemperatureF() const;
    bool isDataValid() const;
    DHTFullEntity* getEntity();
};

DHTSensor::DHTSensor(int pin_number, DHTType type) : pin_number(pin_number), sensorType(type), humidity(0.0), temperatureC(0.0), temperatureF(0.0), dataValid(false) {
    int dhtType = (sensorType == DHTType::DHT11) ? DHT11 : DHT22;
    dht = new DHT(pin_number, dhtType);
}

void DHTSensor::update() {
    humidity = dht->readHumidity();
    temperatureC = dht->readTemperature();
    temperatureF = dht->readTemperature(true);
    dataValid = !isnan(humidity) && !isnan(temperatureC);
}

float DHTSensor::getHumidity() const {
    return humidity;
}

float DHTSensor::getTemperatureC() const {
    return temperatureC;
}

float DHTSensor::getTemperatureF() const {
    return temperatureF;
}

bool DHTSensor::isDataValid() const {
    return dataValid;
}

DHTFullEntity* DHTSensor::getEntity() {
    return new DHTFullEntity(0, 0, "DHT Sensor", ModuleTypes::DHT, "", 0, pin_number, sensorType == DHTType::DHT11 ? "DHT11" : "DHT22", 0, 0, 0, 0);
}

#endif // DHT_H
