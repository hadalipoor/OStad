#ifndef IBUTTON_H
#define IBUTTON_H

#include <Arduino.h>
#include <Wire.h>
#include <PCF8574.h>
#include "../../Database/Entities/Modules/ButtonFullEntity.h"

enum class ButtonType { PIN, PCF8574 };
enum class ClickType { None, Clicked, LongPressClicked };

class IButton
{
public:
    
    virtual void setOnClick(void (*function)(IButton*)) = 0;
    virtual void setOnLongPress(void (*function)(IButton*)) = 0;
    virtual void setDebounceDelay(unsigned long delay) = 0;
    virtual void setLongPressTime(unsigned long time) = 0;
    virtual bool getState() = 0;
    virtual String getName() = 0;
    virtual void update() = 0;
    virtual ButtonFullEntity* getEntity() = 0;
    virtual ~IButton() {}
};

#endif
