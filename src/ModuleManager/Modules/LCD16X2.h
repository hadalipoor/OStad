#ifndef LCD16x2_H
#define LCD16x2_H

#include "ModuleTypes.h"
#include <SPI.h>
#include <Wire.h>
#include "ILCD16X2.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../../Context.h"
#include "../../Database/Entities/Modules/LCDFullEntity.h"

enum LCD16X2Functions{DRAWTEXT, CLEAN};
class LCD16X2 : public ILCD16X2 {
private:
    Context* context;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int SCREEN_ADDRESS;
    int OLED_RESET = -1;
    Adafruit_SSD1306 display;
    String ip;
    String protocolType;
    String callLCD16X2Api(LCD16X2Functions function, String data);

public:
    LCD16X2(Context* context, int module_id, int serverId, String name, int device_id, int address, int width, int height);
    void drawText(String text, int textSize) override;
    void Clean() override;
    LCDFullEntity* getEntity() override;
    int getWidth() override;
    int getHeight() override;
    String getLCDType(LCDTypes lcdType) override;
    LCDTypes getLCDType(String lcdTypeStr) override;
};

LCD16X2::LCD16X2(Context* context, int module_id, int serverId, String name, int device_id, int address, int width, int height)
    : ILCD16X2(module_id, serverId, name, ModuleTypes::LCD, device_id), display(width, height, &Wire, OLED_RESET) {
    this->context = context;
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    SCREEN_ADDRESS = address;
    protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
    
    if(device_id == context->getDeviceManager()->deviceId)
    {
        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;);  // Don't proceed, loop forever
        }
        display.display();
        delay(1000);  // Pause for 2 seconds

        // Initialize display
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(5, 5);
        display.println("OStad");
        display.display();
        delay(2000);
    }
    else
    {
        protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
        ModulesController* modulesController = new ModulesController(context, storageType);
        LCDFullEntity* lcdFullEntity = modulesController->getLCDByServerId(serverId);
        int deviceId = lcdFullEntity->DeviceId;
        DevicesController* devicesController = new DevicesController(context, storageType);
        DevicesEntity device = devicesController->GetById(deviceId);
        ip = device.getIP();
    }
}


String LCD16X2::callLCD16X2Api(LCD16X2Functions function, String data)
{
    String functionStr = "";
    switch(function)
    {
        case CLEAN:
            functionStr = "clean";
            break;
        case DRAWTEXT:
            functionStr = "draw_text";
        default:
            functionStr = "get_state";
    }

    String endpoint = protocolType + "://" + ip + "/lcd16x2controller/"+ functionStr;
    return context->getNetwork()->getApiManager()->makePostRequest(endpoint, data);
}

void LCD16X2::drawText(String text, int textSize) {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        display.clearDisplay();
        display.setTextSize(textSize); 
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(10, 0);
        display.println(text);
        display.display();
    }
    else
    {
        callLCD16X2Api(LCD16X2Functions::DRAWTEXT, "{\"server_id\":"+String(getServerId()) + "}");
    }
}

void LCD16X2::Clean() {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        display.clearDisplay();
        display.display();
    }
    else
    {
        callLCD16X2Api(LCD16X2Functions::CLEAN, "{\"server_id\":"+String(getServerId()) + "}");
    }
}

int LCD16X2::getWidth()
{
    return SCREEN_WIDTH;
}

int LCD16X2::getHeight()
{
    return SCREEN_HEIGHT;
}


LCDFullEntity* LCD16X2::getEntity() {
    String lcdTypeStr = getLCDType(LCDTypes::LCD_16X2);
    return new LCDFullEntity(0, getModuleID(), getName(), SCREEN_ADDRESS, SCREEN_WIDTH, SCREEN_HEIGHT, lcdTypeStr, getDeviceID(), getServerId());
}

String LCD16X2::getLCDType(LCDTypes lcdType) {
    switch (lcdType) {
        case LCDTypes::LCD_16X2: return "LCD16X2";
        case LCDTypes::OLED_LCD: return "OLED";
        default: return "Unknown";
    }
}

LCDTypes LCD16X2::getLCDType(String lcdTypeStr) {
    if (lcdTypeStr == "LCD16X2") {
        return LCDTypes::LCD_16X2;
    } else if (lcdTypeStr == "OLED") {
        return LCDTypes::OLED_LCD;
    }
    return LCDTypes::LCD_16X2; // Default case to handle undefined types
}

#endif // LCD16X2_H
