#ifndef LCD16x2_H
#define LCD16x2_H

#include "ModuleTypes.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../../Database/Entities/Modules/LCDFullEntity.h"

class LCD16X2
{
private:
    String name;
    String connectionType;
    int nodeId;
    int SCREEN_WIDTH = 128; // OLED display width, in pixels
    int SCREEN_HEIGHT = 32; // OLED display height, in pixels
    int SCREEN_ADDRESS = 0x3C;
    int OLED_RESET = -1;
    Adafruit_SSD1306 display;

public:
    LCD16X2(String _name, int address, int width, int hight);
    void drawText(String text, int textSize);
    void Clean();
    LCDFullEntity* getEntity();
    static String getLCDType(LCDTypes lcdType);
    static LCDTypes getLCDType(String lcdTypeStr);
};

LCD16X2::LCD16X2(String _name, int address, int width, int height) : display(width, height, &Wire, OLED_RESET)
{
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    SCREEN_ADDRESS = address;
    name = _name;
    connectionType = "";
    nodeId = 0;
    
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(5, 5);
    display.println("E-B-P");
    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000);
}

LCDFullEntity* LCD16X2::getEntity()
{
    String lcdTypeStr = getLCDType(LCDTypes::LCD_16X2);
    LCDFullEntity *lcdEntity = new LCDFullEntity(0, 0, name, ModuleTypes::LCD, connectionType, nodeId, -1,  SCREEN_ADDRESS, SCREEN_HEIGHT, SCREEN_WIDTH, lcdTypeStr);
    return lcdEntity;
}

void LCD16X2::drawText(String text, int textSize)
{
    display.clearDisplay();

    display.setTextSize(textSize); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.println(text);
    display.display();
}

void LCD16X2::Clean()
{
    display.clearDisplay();
    display.display();
}

String LCD16X2::getLCDType(LCDTypes lcdType)
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

LCDTypes LCD16X2::getLCDType(String lcdTypeStr)
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
#endif