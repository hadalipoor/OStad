#ifndef RELAY_H
#define RELAY_H

#include "IRelay.h"
#include "../../Context.h"
#include "../../Config/Device/DeviceConfigKeys.h"
#include "../../Database/Controllers/Modules/DevicesController.h"
#include "../../Database/Controllers/Modules/ModulesController.h"

class Relay: public IRelay
{
private:
    Context*  context;
    bool state;
    unsigned long delay_millis;
    int pin_number;
    unsigned long start_time;
    bool normallyOpen;
    int serverId;
    String ip;
    String protocolType;
    enum RelayFunctions{TURN_ON, TURN_OFF, TURN_ON_AFTER_DELAY, TURN_OFF_AFTER_DELAY, TURN_ON_FOR_DELAY, TURN_OFF_FOR_DELAY,
                        GET_STATE, GET_NORMALLY_OPEN, SET_NORMALLY_OPEN, SET_PIN_NUMBER, GET_PIN_NUMBER, GET_ENTITY, GET_SERVER_ID, SET_SERVER_ID};
    String callRelayApi(RelayFunctions function, String data);
    
    enum RelayMood { IDLE, TURNING_ON_AFTER_DELAY, TURNING_OFF_AFTER_DELAY, TURNING_ON_FOR_DELAY, TURNING_OFF_FOR_DELAY } relay_mood;

public:
    Relay(Context* context, int module_id, int id, String name, int device_id, int pin_number, String ip, bool normallyOpen = true);
    Relay(Context* context, int module_id, int id, String name, int device_id, int pin_number, String ip, bool normallyOpen, int serverId);

    void turnOn() override;
    void turnOff() override;
    bool getState() override;
    void update() override;
    void turnOnAfterDelay(unsigned long delay_millis) override;
    void turnOffAfterDelay(unsigned long delay_millis) override;
    void turnOnForDelay(unsigned long delay_millis) override;
    void turnOffForDelay(unsigned long delay_millis) override;
    bool getNormallyOpen();
    void setNormallyOpen(bool normallyOpen);
    int getPinNumber() override;
    void setPinNumber(int pinNumber) override;
    RelayFullEntity* getEntity() override;
    int getServerId() override;
    void setServerId(int serverId) override;
};

Relay::Relay(Context* context, int module_id, int id, String name, int device_id, int pin_number, String ip, bool normallyOpen, int server_id)
    : IRelay(module_id, id, name, ModuleTypes::RELAY, device_id) ,pin_number(pin_number), state(false), normallyOpen(normallyOpen), relay_mood(IDLE), context(context), serverId(server_id), ip(ip)
{
    pinMode(pin_number, OUTPUT);
    digitalWrite(pin_number, normallyOpen ? LOW : HIGH);
    protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
    ModulesController* modulesController = new ModulesController(context, storageType);
    RelayFullEntity relayEntity = modulesController->getRelayByServerId(server_id);
    int deviceId = relayEntity.DeviceId;
    DevicesController* devicesController = new DevicesController(context, storageType);
    DevicesEntity device = devicesController->GetById(deviceId);
    ip = device.getIP();
}
Relay::Relay(Context* context, int module_id, int id, String name, int device_id, int pin_number, String ip, bool normallyOpen)
    : Relay(context, module_id, id, name, device_id, pin_number, ip, normallyOpen, 0)
{

}

String Relay::callRelayApi(RelayFunctions function, String data)
{
    String functionStr = "";
    switch(function)
    {
        case TURN_ON:
            functionStr = "turn_on";
            break;
        case TURN_OFF:
            functionStr = "turn_off";
        case GET_STATE:
            functionStr = "get_state";
            break;
        case TURN_ON_AFTER_DELAY:
            functionStr = "turn_on_after_delay";
            break;
        case TURN_OFF_AFTER_DELAY:
            functionStr = "turn_off_after_delay";
            break;
        case TURN_ON_FOR_DELAY:
            functionStr = "turn_on_for_delay";
            break;
        case TURN_OFF_FOR_DELAY:
            functionStr = "turn_off_for_delay";
            break;
        case SET_NORMALLY_OPEN:
            functionStr = "set_normally_open";
            break;
        case GET_NORMALLY_OPEN:
            functionStr = "get_normally_open";
            break;
        case SET_PIN_NUMBER:
            functionStr = "set_pin_number";
            break;
        case GET_PIN_NUMBER:
            functionStr = "get_pin_number";
            break;
        case GET_ENTITY:
            functionStr = "get_entity";
            break;
        default:
            functionStr = "get_state";
    }

    String endpoint = protocolType + "://" + ip + "/relaycontroller/"+ functionStr +"?" + data;
    return context->getNetwork()->getApiManager()->makePostRequest(endpoint, "");
}

RelayFullEntity* Relay::getEntity()
{
    return new RelayFullEntity(getID(), getModuleID(), getName(), ModuleTypes::RELAY, pin_number, normallyOpen, serverId, getDeviceID());
}

void Relay::turnOn()
{
    if (getDeviceID() == context->getDeviceManager()->deviceId)
    {
        digitalWrite(pin_number, normallyOpen ? HIGH : LOW);
        if (!state)
        {
            state = true;
        }        
    }
    else
    {
        callRelayApi(RelayFunctions::TURN_ON, "server_id="+String(serverId));
    }
    
}

void Relay::turnOff()
{
    if (getDeviceID() == context->getDeviceManager()->deviceId)
    {    
        digitalWrite(pin_number, normallyOpen ? LOW : HIGH);
        if(state)
        {
            state = false;
        }
    }
    else
    {
        callRelayApi(RelayFunctions::TURN_OFF, "server_id="+String(serverId));
    }
}

bool Relay::getState()
{
    if (getDeviceID() == context->getDeviceManager()->deviceId)
    {    
        return state;
    }
    else
    {
        callRelayApi(RelayFunctions::GET_STATE, "server_id="+String(serverId));
    }
}

void Relay::update()
{
    switch(relay_mood)
    {
        case TURNING_ON_AFTER_DELAY:
            if (millis() - start_time >= delay_millis)
            {
                turnOn();
                relay_mood = IDLE;
            }
            break;
        case TURNING_OFF_AFTER_DELAY:
            if (millis() - start_time >= delay_millis)
            {
                turnOff();
                relay_mood = IDLE;
            }
            break;
        case TURNING_ON_FOR_DELAY:
            if (millis() - start_time >= delay_millis)
            {
                turnOff();
                relay_mood = IDLE;
            }
            break;
        case TURNING_OFF_FOR_DELAY:
            if (millis() - start_time >= delay_millis)
            {
                turnOn();
                relay_mood = IDLE;
            }
            break;
    }
}

void Relay::turnOnAfterDelay(unsigned long delay_millis)
{
    if (getDeviceID() == context->getDeviceManager()->deviceId)
    {
        this->delay_millis = delay_millis;
        start_time = millis();
        relay_mood = TURNING_ON_AFTER_DELAY;
    }
    else
    {
        callRelayApi(RelayFunctions::TURN_ON_AFTER_DELAY, "server_id="+String(serverId) + "&delay_millis=" + String(delay_millis));
    }
}

void Relay::turnOffAfterDelay(unsigned long delay_millis)
{
    if (getDeviceID() == context->getDeviceManager()->deviceId)
    {
        this->delay_millis = delay_millis;
        start_time = millis();
        relay_mood = TURNING_OFF_AFTER_DELAY;
    }
    else
    {
        callRelayApi(RelayFunctions::TURN_OFF_AFTER_DELAY, "server_id="+String(serverId) + "&delay_millis=" + String(delay_millis));
    }
}

void Relay::turnOnForDelay(unsigned long delay_millis)
{
    if (getDeviceID() == context->getDeviceManager()->deviceId)
    {
        turnOn();
        this->delay_millis = delay_millis;
        start_time = millis();
        relay_mood = TURNING_ON_FOR_DELAY;
    }
    else
    {
        callRelayApi(RelayFunctions::TURN_ON_FOR_DELAY, "server_id="+String(serverId) + "&delay_millis=" + String(delay_millis));
    }
}

void Relay::turnOffForDelay(unsigned long delay_millis)
{
    if (getDeviceID() == context->getDeviceManager()->deviceId)
    {
        turnOff();
        this->delay_millis = delay_millis;
        start_time = millis();
        relay_mood = TURNING_OFF_FOR_DELAY;
    }
    else
    {
        callRelayApi(RelayFunctions::TURN_OFF_FOR_DELAY, "server_id="+String(serverId) + "&delay_millis=" + String(delay_millis));
    }
}

int Relay::getPinNumber()
{
    return pin_number;
}

void Relay::setPinNumber(int pinNumber)
{
    pin_number = pinNumber;
    if (getDeviceID() != context->getDeviceManager()->deviceId)
    {
        context->getModules()->getRelay(serverId)->setPinNumber(pinNumber);
    }
    else
    {
        callRelayApi(RelayFunctions::SET_PIN_NUMBER, "server_id="+String(serverId) + "&pin_number=" + String(pinNumber));
    }
}

bool Relay::getNormallyOpen()
{
    return normallyOpen;
}

void Relay::setNormallyOpen(bool _normallyOpen)
{
    normallyOpen = _normallyOpen;
    if (getDeviceID() != context->getDeviceManager()->deviceId)
    {
        context->getModules()->getRelay(serverId)->setNormallyOpen(normallyOpen);
    }
    else
    {
        callRelayApi(RelayFunctions::SET_NORMALLY_OPEN, "server_id="+String(serverId) + "&normally_open=" + _normallyOpen? "true" : "false");
    }
}

int Relay::getServerId()
{
    return serverId;
}

void Relay::setServerId(int serverId)
{
    serverId = serverId;
}

#endif
