#ifndef SOILMOISTURE_H
#define SOILMOISTURE_H

#include "ISoilMoistureSensor.h"
#include <string>
#include "ModuleTypes.h"

class SoilMoistureSensor : public ISoilMoistureSensor {
private:
  String name;
  String connectionType;
  int nodeId;
  int sensorPin;       // Pin connected to the soil moisture sensor
  int dryThreshold;    // Threshold value indicating dry soil
  int wetThreshold;    // Threshold value indicating wet soil

public:
  SoilMoistureSensor(String name, String connectionType, int nodeId, int sensorPin, int dryThreshold, int wetThreshold)
    : name(name), connectionType(connectionType), nodeId(nodeId), sensorPin(sensorPin), dryThreshold(dryThreshold), wetThreshold(wetThreshold) {}

  void initialize() override {
    pinMode(sensorPin, INPUT);
  }

  int readMoisture() override {
    int moisture = analogRead(sensorPin);
    return moisture;
  }

  bool isDry() override {
    int moisture = readMoisture();
    return moisture <= dryThreshold;
  }

  bool isWet() override {
    int moisture = readMoisture();
    return moisture >= wetThreshold;
  }

  String getName() override {
    return name;
  }

  String getConnectionType() override {
    return connectionType;
  }

  int getNodeId() override {
    return nodeId;
  }

  int getSensorPin() override {
    return sensorPin;
  }

  int getDryThreshold() override {
    return dryThreshold;
  }

  int getWetThreshold() override {
    return wetThreshold;
  }

  SoilMoistureFullEntity* getEntity() override
  {
    SoilMoistureFullEntity *soilMoistureEntity = new SoilMoistureFullEntity(0, 0, name, ModuleTypes::SOILMOISTURE, connectionType, nodeId, sensorPin,  dryThreshold, wetThreshold, "Analog");
    return soilMoistureEntity;
  }
};


#endif