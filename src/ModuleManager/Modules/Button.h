#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include <Arduino.h>
#include <Wire.h>
#include <PCF8574.h>
#include "../../Database/Entities/Modules/ButtonFullEntity.h"
#include "ModuleTypes.h"

enum class ButtonType { PIN, PCF8574 };
enum class ClickType { None, Clicked, LongPressClicked };

class Button
{
public:
    using ButtonCallback = std::function<void(Button*)>;
private:
    String name;
    uint8_t pin_number;
    PCF8574* pcf8574;
    ButtonType buttonType;
    bool activeHigh;
    bool pullUpActive;
    bool pressed;
    bool lastState;
    String connectionType;
    int nodeId;
    bool waitingForRelease; // new member variable to track button release
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
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
    Button(uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, ButtonType buttonType, PCF8574* pcf8574);
    Button(uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, ButtonType buttonType);
    Button(uint8_t pin_number, String name, bool activeHigh, bool pullUpActive, String buttonTypeStr);
    Button(uint8_t pin_number, String name, bool activeHigh, bool pullUpActive);
    // Button();
    
    void setOnClick(ButtonCallback function);
    void setOnLongPress(ButtonCallback function);
    void setDebounceDelay(unsigned long delay);
    void setLongPressTime(unsigned long time);
    bool getState();
    String getName();
    void update();
    ButtonFullEntity* getEntity();
    static String getButtonType(ButtonType buttonType);
    static ButtonType getButtonType(String buttonTypeStr);
    int getPinNumber();
    bool getActiveHigh();
    bool getPullUpActive();
};

// Button::Button()
// {
    
// }
Button::Button(uint8_t _pin_number, String _name, bool _activeHigh, bool _pullUpActive, ButtonType _buttonType, PCF8574* _pcf8574)
    : pin_number(_pin_number), activeHigh(_activeHigh), pullUpActive(_pullUpActive), name(_name), 
      pressed(false), lastState(false), lastDebounceTime(0), debounceDelay(60), longPressTime(2000), buttonDownTime(0),
      buttonType(_buttonType), onClickFunction(NULL), onLongPressFunction(nullptr), pcf8574(_pcf8574), onClickSeted(false), onLongPressSeted(false)
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
Button::Button(uint8_t _pin_number, String _name, bool _activeHigh, bool _pullUpActive, ButtonType _buttonType):
    Button(_pin_number, _name, _activeHigh, _pullUpActive, _buttonType, 0)
{

}
Button::Button(uint8_t _pin_number, String _name, bool _activeHigh = true, bool _pullUpActive = false):
    Button(_pin_number, _name, _activeHigh, _pullUpActive, ButtonType::PIN)
{

}

Button::Button(uint8_t _pin_number, String _name, bool _activeHigh, bool _pullUpActive, String _buttonTypeStr):
    Button(_pin_number, _name, _activeHigh, _pullUpActive, Button::getButtonType(_buttonTypeStr))
{

}

ButtonFullEntity* Button::getEntity()
{
    String buttonTypeStr = Button::getButtonType(buttonType);
    ButtonFullEntity *buttonEntity = new ButtonFullEntity(0, 0, name, ModuleTypes::BUTTON, connectionType, nodeId, pin_number,  buttonTypeStr, activeHigh, pullUpActive, debounceDelay);
    return buttonEntity;
}

void Button::update() {
    uint8_t reading;

    if (buttonType == ButtonType::PIN) {
        reading = digitalRead(pin_number);
    } else if (buttonType == ButtonType::PCF8574) {
        reading = pcf8574->digitalRead(pin_number);
    }

    if (activeHigh) {
        reading = !reading;
    }

    if (debounceDelay == 0 && reading == true && onClickSeted)
    {
        onClickFunction(this);
        return;
    }
    
    unsigned long now = millis();
    if (reading != lastState && reading == true) {
        lastDebounceTime = now;
    }

    if ((now - lastDebounceTime) > debounceDelay) {
        if (reading != pressed) {
            pressed = reading;
            if (pressed) {
                // Button pressed
                buttonDownTime = now;
                waitingForRelease = true; // set the flag to wait for button release
            } else {
                // Button released
                unsigned long pressDuration = now - buttonDownTime;
                if (!longPressTriggered && (pressDuration >= debounceDelay)) {
                    // onClickFunction(this);
                }
                longPressTriggered = false; // reset the longPressTriggered flag when the button is released
                waitingForRelease = false; // reset the flag when the button is released
            }
        } else if (waitingForRelease && pressed) {
            // Button is still pressed and waiting for release
            if (now - buttonDownTime > debounceDelay) {
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
    debounceDelay = delay;
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
    return name;
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
    return pin_number;
}

bool Button::getActiveHigh()
{
    return activeHigh;
}

bool Button::getPullUpActive()
{
    return pullUpActive;
}

#endif
