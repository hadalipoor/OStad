#ifndef ILCD_H
#define ILCD_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../../Database/Entities/Modules/LCDFullEntity.h"

enum LCDTypes {OLED_LCD, LCD_16X2};

class ILCD
{
public:
    virtual void drawText(String text, int textSize) = 0;
    virtual void Clean() = 0;
    virtual LCDFullEntity* getEntity() = 0;
    static String getLCDType(LCDTypes lcdType)
    {
        if (lcdType == LCDTypes::LCD_16X2)
        {
            return "LCD16X2";
        }
        else if (lcdType == LCDTypes::OLED_LCD)
        {
            return "OLED";
        }
    }

    static LCDTypes getLCDType(String lcdTypeStr)
    {
        if (lcdTypeStr == "LCD16X2")
        {
            return LCDTypes::LCD_16X2;
        }
        else if (lcdTypeStr == "OLED")
        {
            return LCDTypes::OLED_LCD;
        }    
   
    }
};


#endif