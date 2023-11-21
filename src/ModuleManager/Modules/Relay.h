#ifndef RELAY_H
#define RELAY_H

#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/RelayFullEntity.h"

class Relay
{
private:
    String name;
    int pin_number;
    String connectionType;
    int nodeId;
    bool state;
    bool normallyOpen;
    unsigned long delay_millis;
    unsigned long start_time;
    enum { IDLE, TURN_ON_AFTER_DELAY, TURN_OFF_AFTER_DELAY, TURN_ON_FOR_DELAY, TURN_OFF_FOR_DELAY } mode;

public:
    Relay(int pin_number, String name, bool normallyOpen = true);

    void turnOn();
    void turnOff();
    bool getState();
    void update();
    void turnOnAfterDelay(unsigned long delay_millis);
    void turnOffAfterDelay(unsigned long delay_millis);
    void turnOnForDelay(unsigned long delay_millis);
    void turnOffForDelay(unsigned long delay_millis);
    RelayFullEntity* getEntity();

};

Relay::Relay(int pin_number, String name, bool normallyOpen)
    : pin_number(pin_number), state(false), name(name), normallyOpen(normallyOpen), mode(IDLE)
{
    pinMode(pin_number, OUTPUT);
    digitalWrite(pin_number, normallyOpen ? LOW : HIGH);
}

RelayFullEntity* Relay::getEntity()
{
    return new RelayFullEntity(0, 0, name, ModuleTypes::RELAY, connectionType, nodeId, pin_number, normallyOpen);
}

void Relay::turnOn()
{
    digitalWrite(pin_number, normallyOpen ? HIGH : LOW);
    if (!state)
    {
        state = true;
    }
}

void Relay::turnOff()
{
    digitalWrite(pin_number, normallyOpen ? LOW : HIGH);
    if(state)
    {
        state = false;
    }
}

bool Relay::getState()
{
    return state;
}

void Relay::update()
{
    switch(mode)
    {
        case TURN_ON_AFTER_DELAY:
            if (millis() - start_time >= delay_millis)
            {
                turnOn();
                mode = IDLE;
            }
            break;
        case TURN_OFF_AFTER_DELAY:
            if (millis() - start_time >= delay_millis)
            {
                turnOff();
                mode = IDLE;
            }
            break;
        case TURN_ON_FOR_DELAY:
            if (millis() - start_time >= delay_millis)
            {
                turnOff();
                mode = IDLE;
            }
            break;
        case TURN_OFF_FOR_DELAY:
            if (millis() - start_time >= delay_millis)
            {
                turnOn();
                mode = IDLE;
            }
            break;
    }
}

void Relay::turnOnAfterDelay(unsigned long delay_millis)
{
    this->delay_millis = delay_millis;
    start_time = millis();
    mode = TURN_ON_AFTER_DELAY;
}

void Relay::turnOffAfterDelay(unsigned long delay_millis)
{
    this->delay_millis = delay_millis;
    start_time = millis();
    mode = TURN_OFF_AFTER_DELAY;
}

void Relay::turnOnForDelay(unsigned long delay_millis)
{
    turnOn();
    this->delay_millis = delay_millis;
    start_time = millis();
    mode = TURN_ON_FOR_DELAY;
}

void Relay::turnOffForDelay(unsigned long delay_millis)
{
    turnOff();
    this->delay_millis = delay_millis;
    start_time = millis();
    mode = TURN_OFF_FOR_DELAY;
}

#endif
