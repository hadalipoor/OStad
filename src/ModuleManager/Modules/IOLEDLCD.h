#ifndef IOLEDLCD_H
#define IOLEDLCD_H

#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/LCDFullEntity.h"
#include "BaseModule.h"

class IOLEDLCD: public BaseModule
{
public:
    IOLEDLCD(int module_id, int serverId, String name, String moduleType, int device_id):
        BaseModule(module_id, serverId, name, moduleType, device_id){}
    
    virtual void begin() = 0;
    virtual void printAt(uint8_t col, uint8_t row, const String& message) = 0;
    virtual void print(const String& message) = 0;
    virtual void drawText(String text, int textSize) = 0;
    virtual void Clean() = 0;
    virtual int getAddress() = 0;
    virtual int getCol() = 0;
    virtual int getRows() = 0;
    static String getLCDType(LCDTypes lcdType);
    static LCDTypes getLCDTypefromString(String lcdTypeStr);
    virtual LCDFullEntity* getEntity() = 0;
};

String IOLEDLCD::getLCDType(LCDTypes lcdType)
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

LCDTypes IOLEDLCD::getLCDTypefromString(String lcdTypeStr)
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
#endif //IOLEDLCD_H