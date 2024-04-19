#ifndef SOILMOISTURE_H
#define SOILMOISTURE_H

#include <string>
#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/SoilMoistureFullEntity.h"

class SoilMoistureSensor {
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

  void initialize() {
    pinMode(sensorPin, INPUT);
  }

  int readMoisture() {
    int moisture = analogRead(sensorPin);
    return moisture;
  }

  bool isDry() {
    int moisture = readMoisture();
    return moisture <= dryThreshold;
  }

  bool isWet() {
    int moisture = readMoisture();
    return moisture >= wetThreshold;
  }

  String getName() {
    return name;
  }

  String getConnectionType() {
    return connectionType;
  }

  int getNodeId() {
    return nodeId;
  }

  int getSensorPin() {
    return sensorPin;
  }

  int getDryThreshold() {
    return dryThreshold;
  }

  int getWetThreshold() {
    return wetThreshold;
  }

  SoilMoistureFullEntity* getEntity()
  {
    SoilMoistureFullEntity *soilMoistureEntity = new SoilMoistureFullEntity(0, 0, name, ModuleTypes::SOILMOISTURE, connectionType, nodeId, sensorPin,  dryThreshold, wetThreshold, "Analog");
    return soilMoistureEntity;
  }
};


#endif