#ifndef OLEDLCD_H
#define OLEDLCD_H

#include "ModuleTypes.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../../Database/Entities/Modules/LCDFullEntity.h"

class OLEDLCD {
  private:
    String name;
    uint8_t lcdColumns; 
    uint8_t lcdRows;
    uint8_t lcdAddress;
    String connectionType;
    int nodeId;
    LiquidCrystal_I2C lcd;

  public:
    OLEDLCD(String name, uint8_t address, uint8_t columns, uint8_t rows) 
      : lcdColumns(columns), lcdRows(rows), lcdAddress(address), name(name), lcd(address, columns, rows)
      {
        begin();
      }

    void begin() {
      lcd.begin(lcdColumns, lcdRows);
      lcd.init();
      lcd.init();
      lcd.backlight();
      lcd.clear();
    }

    LCDFullEntity* getEntity()
    {
        String lcdTypeStr = getLCDType(LCDTypes::LCD_16X2);
        LCDFullEntity *lcdEntity = new LCDFullEntity(0, 0, name, ModuleTypes::LCD, connectionType, nodeId, -1,  lcdAddress, lcdRows, lcdColumns, lcdTypeStr);
        return lcdEntity;
    }
    void print(const String& message) {
      lcd.print(message);
    }

    void printAt(uint8_t col, uint8_t row, const String& message) {
      lcd.setCursor(col, row);
      lcd.print(message);
    }

    void drawText(String text, int textSize)
    {
      print(text);
    }

    void Clean(){
      lcd.clear();
    }

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