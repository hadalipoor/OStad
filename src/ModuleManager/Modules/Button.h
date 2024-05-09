#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <Arduino.h>
#include <Wire.h>
#include <PCF8574.h>
#include "../../Database/Entities/Modules/ButtonFullEntity.h"
#include "ModuleTypes.h"
#include "BaseModule.h"
#include "../../Context.h"
#include "IButton.h"

class Button: public IButton
{
private:
    Context* context;
    uint8_t _pin_number;
    PCF8574* _pcf8574;
    ButtonType _buttonType;
    bool _activeHigh;
    bool _pullUpActive;
    bool pressed;
    bool lastState;
    bool waitingForRelease; // new member variable to track button release
    unsigned long lastDebounceTime;
    unsigned long _debounceDelay;
    unsigned long longPressTime;
    unsigned long buttonDownTime;
    bool reading;
    long press_time;
    bool longPressTriggered = false;
    uint8_t pcf_address;
    bool onClickSeted;
    bool onLongPressSeted;


    ButtonCallback onClickFunction;
    ButtonCallback onLongPressFunction;
public:
    Button(Context* context, uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, ButtonType buttonType, PCF8574* pcf8574,int deviceId, int id, int module_id);
    Button(Context* context, uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, ButtonType buttonType, PCF8574* pcf8574,int deviceId);
    Button(Context* context, uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, int deviceId, int id, int module_id);
    Button(Context* context, uint8_t pin_number, String name, bool activeHigh, bool pullUpActive);
    
    // Button();
    
    void setOnClick(ButtonCallback function) override;
    void setOnLongPress(ButtonCallback function) override;
    void setDebounceDelay(unsigned long delay) override;
    void setLongPressTime(unsigned long time) override;
    bool getState() override;
    String getName() override;
    void update() override;
    ButtonFullEntity* getEntity() override;
    static String getButtonType(ButtonType buttonType);
    static ButtonType getButtonType(String buttonTypeStr);
    int getPinNumber() override;
    bool getActiveHigh() override;
    bool getPullUpActive() override;
};

// Button::Button()
// {
    
// }

Button::Button(Context* context, uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, ButtonType buttonType, PCF8574* pcf8574,int deviceId, int id, int module_id):
IButton(module_id, id, name, ModuleTypes::BUTTON, deviceId),_pin_number(pin_number), _activeHigh(activeHigh), _pullUpActive(pullUpActive),
      pressed(false), lastState(false), lastDebounceTime(0), _debounceDelay(60), longPressTime(2000), buttonDownTime(0),
      _buttonType(buttonType), onClickFunction(NULL), onLongPressFunction(nullptr), _pcf8574(pcf8574), onClickSeted(false), onLongPressSeted(false)
{
    if (buttonType == ButtonType::PIN)
    {
        pinMode(pin_number, pullUpActive ? INPUT_PULLUP : INPUT);
    }
    else if(buttonType == ButtonType::PCF8574)
    {
        // pcf8574 = new PCF8574(pcf_address);//read from settings
	    
        pcf8574->pinMode(pin_number, INPUT);
        

    }
    lastState = false;
    pressed = false;
}

Button::Button(Context* context, uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, ButtonType buttonType, PCF8574* pcf8574,int deviceId)
    : Button(context, pin_number, name, activeHigh, pullUpActive, buttonType, pcf8574, deviceId, 0, 0)
{
    
}
Button::Button(Context* context, uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, int deviceId, int id, int module_id)
    : Button(context, pin_number, name, activeHigh, pullUpActive, ButtonType::PIN, nullptr, deviceId, id, module_id)
{

}
Button::Button(Context* context, uint8_t pin_number, String name, bool activeHigh, bool pullUpActive)
    : Button(context, pin_number, name, activeHigh, pullUpActive, ButtonType::PIN, NULL, 0, 0, 0)
{

}


ButtonFullEntity* Button::getEntity()
{
    String buttonTypeStr = Button::getButtonType(_buttonType);
    ButtonFullEntity *buttonEntity = new ButtonFullEntity(this->getID(), _module_id, _name, ModuleTypes::BUTTON, _device_id, _pin_number,  buttonTypeStr, _activeHigh, _pullUpActive, _debounceDelay);
    return buttonEntity;
}

void Button::update() {
    uint8_t reading;

    if (_buttonType == ButtonType::PIN) {
        reading = digitalRead(_pin_number);
    } else if (_buttonType == ButtonType::PCF8574) {
        reading = _pcf8574->digitalRead(_pin_number);
    }

    if (_activeHigh) {
        reading = !reading;
    }

    if (_debounceDelay == 0 && reading == true && onClickSeted)
    {
        onClickFunction(this);
        return;
    }
    
    unsigned long now = millis();
    if (reading != lastState && reading == true) {
        lastDebounceTime = now;
    }

    if ((now - lastDebounceTime) > _debounceDelay) {
        if (reading != pressed) {
            pressed = reading;
            if (pressed) {
                // Button pressed
                buttonDownTime = now;
                waitingForRelease = true; // set the flag to wait for button release
            } else {
                // Button released
                unsigned long pressDuration = now - buttonDownTime;
                if (!longPressTriggered && (pressDuration >= _debounceDelay)) {
                    // onClickFunction(this);
                }
                longPressTriggered = false; // reset the longPressTriggered flag when the button is released
                waitingForRelease = false; // reset the flag when the button is released
            }
        } else if (waitingForRelease && pressed) {
            // Button is still pressed and waiting for release
            if (now - buttonDownTime > _debounceDelay) {
                // Button held down after debounce delay, trigger onClickFunction again
                if (onClickSeted)
                {
                    onClickFunction(this);
                }
                waitingForRelease = false; // reset the flag to wait for release again
                
            }
        } else if (!longPressTriggered && pressed && longPressTime > 0 && (now - buttonDownTime) > longPressTime) {
            // The button is pressed and longPressTime passed.
            if (onLongPressSeted)
            {
                onLongPressFunction(this);
                longPressTriggered = true;
            }
            
        }
    }
    lastState = reading;
}

void Button::setOnClick(ButtonCallback function)
{
    onClickSeted = true;
    onClickFunction = function;
}

void Button::setOnLongPress(ButtonCallback function)
{
    onLongPressSeted = true;
    onLongPressFunction = function;
}

void Button::setDebounceDelay(unsigned long delay)
{
    _debounceDelay = delay;
}

void Button::setLongPressTime(unsigned long time)
{
    longPressTime = time;
}

bool Button::getState()
{
    return pressed;
}

String Button::getName()
{
    return _name;
}

String Button::getButtonType(ButtonType buttonType)
{
    if (buttonType == ButtonType::PIN)
    {
        return "PIN";
    }
    else if (buttonType == ButtonType::PCF8574)
    {
        return "PCF8574";
    }
}

ButtonType Button::getButtonType(String buttonTypeStr)
{
    if (buttonTypeStr == "PIN")
    {
        return ButtonType::PIN;
    }
    else if (buttonTypeStr == "PCF8574")
    {
        return ButtonType::PCF8574;
    }    

}

int Button::getPinNumber()
{
    return _pin_number;
}

bool Button::getActiveHigh()
{
    return _activeHigh;
}

bool Button::getPullUpActive()
{
    return _pullUpActive;
}

#endif
