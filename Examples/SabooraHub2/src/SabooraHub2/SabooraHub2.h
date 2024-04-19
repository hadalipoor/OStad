#ifndef SABOORAHUB2_H
#define SABOORAHUB2_H

#include "ISabooraHub2.h"
#include "../AppContext.h"
#include "../Config/DefaultSabooraHub2Configs.h"
#include <HTTPClient.h>

class SabooraHub2 : public ISabooraHub2 {
private:
    AppContext* context;

public:
    SabooraHub2(AppContext* context);
    
    void initialize() override;
    void update() override;
    void toggleGardeLight();
    void toggleGazeboLight();
    void OpenTheDoor() override;
};

SabooraHub2::SabooraHub2(AppContext* context)
    : context(context) {}

void SabooraHub2::initialize() {
        context->getDeviceManager()->remote1Button()->setOnClick([&](Button* button){
        Serial.println("remote 1 Clicked");
        OpenTheDoor();
    });

    context->getDeviceManager()->remote2Button()->setOnClick([&](Button* button){
        Serial.println("remote 2 Clicked");
        toggleGardeLight();
    });

    context->getDeviceManager()->remote3Button()->setOnClick([&](Button* button){
        Serial.println("remote 3 Clicked");
        toggleGazeboLight();
    });
}

void SabooraHub2::update() {

}

void SabooraHub2::toggleGardeLight()
{
    if (!context->getDeviceManager()->gazebo1lightRelay()->getState())
    {
        context->getDeviceManager()->gazebo1lightRelay()->turnOn();
        context->getDeviceManager()->gazebo2lightRelay()->turnOn();
    }
    else
    {
        context->getDeviceManager()->gazebo1lightRelay()->turnOff();
        context->getDeviceManager()->gazebo2lightRelay()->turnOff();
    }    
}

void SabooraHub2::toggleGazeboLight()
{
    if (!context->getDeviceManager()->gardenRelay()->getState())
    {
        context->getDeviceManager()->gardenRelay()->turnOn();
    }
    else
    {
        context->getDeviceManager()->gardenRelay()->turnOff();
    }
    
}

void SabooraHub2::OpenTheDoor()
{
    HTTPClient http;
    String status;
    
    String serverPath = "http://192.168.4.2/tagcontroller/openDoor";
    
    // Your Domain name with URL path or IP address with path
    
    http.begin(serverPath.c_str());
    
    // If you need Node-RED/server authentication, insert user and password below
    //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
    
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

}

#endif //SABOORAHUB2_H
