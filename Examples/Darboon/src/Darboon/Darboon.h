#ifndef DARBOON_H
#define DARBOON_H

#include "IDarboon.h"
#include "../AppContext.h"
#include "../Config/DefaultDarboonConfigs.h"
#include "../Database/Controllers/GuestsController.h"
#include "../Database/Controllers/DoorLogController.h"
#include <HTTPClient.h>

class Darboon : public IDarboon {
private:
    AppContext* context;
    void onNewTagRecieve(String uid);
    void SwitchGardenLights(bool on);

public:
    Darboon(AppContext* context);
    
    void initialize() override;
    void update() override;
    void openTheDoor() override;
};

Darboon::Darboon(AppContext* context)
    : context(context) {}

void Darboon::SwitchGardenLights(bool on)
{
    HTTPClient http;
    String status;
    
    if(on){status="on";}else{status="off";}

    String serverPath = "http://192.168.4.2/light/switch_garden_lights?status="+status;
    
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

void Darboon::onNewTagRecieve(String uid)
{
    // Serial.println("onNewTagRecieve");
    GuestsController* guestController = new GuestsController(context, storageType);
    GuestsEntity guest = guestController->getGuestByUid(uid);
    if (guest.GetValue(GuestsEntity::COLUMN_NAME) != "")
    {
        openTheDoor();
        DoorLogController* doorLogController = new DoorLogController(context, storageType);
        DoorLogEntity* doorLog = new DoorLogEntity(uid.toInt(), guest.id, true, context->systemContext->getClock()->now());
        doorLogController->Add(*doorLog);
    }
    else
    {
        GuestsEntity waitingGuest = guestController->getWaitingGuest();
        if (waitingGuest.GetValue(GuestsEntity::COLUMN_UID) == "WAITING")
        {
            waitingGuest.SetValue(GuestsEntity::COLUMN_UID, uid);
            guestController->Update(waitingGuest);
        }
        else
        {
            DoorLogController* doorLogController = new DoorLogController(context, storageType);
            DoorLogEntity* doorLog = new DoorLogEntity(uid.toInt(), 0, false, context->systemContext->getClock()->now());
            doorLogController->Add(*doorLog);
        }
        
    }
}

void Darboon::initialize() {
    context->getDeviceManager()->mainRFID()->setOnNewTag([&](String uid){this->onNewTagRecieve(uid);});
    context->getDeviceManager()->remote1Button()->setOnClick([&](Button* button){
        Serial.println("remote 1 Clicked");
        openTheDoor();
    });

    context->getDeviceManager()->remote2Button()->setOnClick([&](Button* button){
        Serial.println("remote 2 Clicked");
        SwitchGardenLights(true);
    });

    context->getDeviceManager()->remote3Button()->setOnClick([&](Button* button){
        Serial.println("remote 3 Clicked");
        SwitchGardenLights(false);
    });
}

void Darboon::update() {

}

void Darboon::openTheDoor() {
    context->getDeviceManager()->doorRelay()->turnOnForDelay(1000);
}

#endif //DARBOON_H
