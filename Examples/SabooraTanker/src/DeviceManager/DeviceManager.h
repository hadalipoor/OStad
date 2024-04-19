#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../AppContext.h"
#include <OStad.h>

class DeviceManager : public IDeviceManager
{
private:
    AppContext* appContext;
    Button* _resetButton;
    long duration;
    const int trig = 25;
    const int echo = 26;
    void calculateDistance();
    float distanceValues[20] = {0}; // Initialize all elements to 0
    int distanceIndex = 0; // Index for the next distance value to update
    float _distance = 0; // Current average distance
    float _sumOfDistances = 0; // Sum of the last 20 distance values

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    int getCapacity() override; // This returns the average distance
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {}

void DeviceManager::initialize()
{
    _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

void DeviceManager::update()
{
    _resetButton->update();
    calculateDistance();
}

Button* DeviceManager::resetButton()
{
    return appContext->systemContext->getModules()->getButton("resetButton");
}

int DeviceManager::getCapacity()
{
    return _distance;
}

void DeviceManager::calculateDistance()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);

    float newDistance = duration * 0.034 / 2;
    // Subtract the oldest distance value from the sum and add the new one
    _sumOfDistances -= distanceValues[distanceIndex];
    _sumOfDistances += newDistance;

    // Update the circular buffer with the new distance value
    distanceValues[distanceIndex] = newDistance;
    distanceIndex = (distanceIndex + 1) % 20; // Ensure the index wraps around

    // Calculate the new average distance
    _distance = _sumOfDistances / 20;
    Serial.println(_distance);
}

#endif
