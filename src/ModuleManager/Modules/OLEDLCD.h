#ifndef OLEDLCD_H
#define OLEDLCD_H

#include "ModuleTypes.h"
#include "../../Context.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "IOLEDLCD.h"

enum OLEDLCDFunctions{PRINTAT, PRINT, OLEDDRAWTEXT, OLEDCLEAN};

class OLEDLCD: public IOLEDLCD {
  private:
    Context* context;
    uint8_t lcdColumns; 
    uint8_t lcdRows;
    uint8_t lcdAddress;
    LiquidCrystal_I2C lcd;
    String ip;
    String protocolType;
    String callOLEDLCDApi(OLEDLCDFunctions function, String data);

public:
  OLEDLCD(int module_id, int id, String name, uint8_t address, uint8_t columns, uint8_t rows, int device_id, int serverId); 
  void begin() override;
  void printAt(uint8_t col, uint8_t row, const String& message) override;
  void print(const String& message) override;
  void drawText(String text, int textSize) override;
  void Clean() override;
  int getAddress() override;
  int getCol() override;
  int getRows() override;
  LCDFullEntity* getEntity() override;
};

OLEDLCD::OLEDLCD(int module_id, int id, String name, uint8_t address, uint8_t columns, uint8_t rows, int device_id, int serverId)
  : IOLEDLCD(module_id, id, name, ModuleTypes::LCD, device_id), lcdColumns(columns), lcdRows(rows), lcdAddress(address), lcd(address, columns, rows)
{
    protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
    if(device_id == context->getDeviceManager()->deviceId)
    {
      begin();
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


String OLEDLCD::callOLEDLCDApi(OLEDLCDFunctions function, String data)
{
    String functionStr = "";
    switch(function)
    {
        case OLEDLCDFunctions::PRINTAT:
            functionStr = "print_at";
            break;
        case OLEDLCDFunctions::PRINT:
            functionStr = "print";
            break;
        case OLEDLCDFunctions::OLEDDRAWTEXT:
            functionStr = "draw_text";
            break;
        case OLEDLCDFunctions::OLEDCLEAN:
            functionStr = "clean";
            break;
        default:
            functionStr = "clean";
    }

    String endpoint = protocolType + "://" + ip + "/oledlcdcontroller/"+ functionStr;
    return context->getNetwork()->getApiManager()->makePostRequest(endpoint, data);
}

void OLEDLCD::begin() {
  lcd.begin(lcdColumns, lcdRows);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

LCDFullEntity* OLEDLCD::getEntity()
{
    LCDFullEntity *lcdEntity = new LCDFullEntity(0, _module_id, getName(), lcdAddress, lcdRows, lcdColumns, getLCDType(LCDTypes::OLED_LCD),_device_id,  getServerId());
    return lcdEntity;
}

void OLEDLCD::print(const String& message) {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
      lcd.print(message);
    }
    else
    {
      callOLEDLCDApi(OLEDLCDFunctions::PRINT, "{\"server_id\":"+String(getServerId()) + ", \"message\": \"" + message + "\"}");
    }
}

void OLEDLCD::printAt(uint8_t col, uint8_t row, const String& message) {
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
      lcd.setCursor(col, row);
      lcd.print(message);
    }
    else
    {
      callOLEDLCDApi(OLEDLCDFunctions::PRINTAT, "{\"server_id\":"+String(getServerId()) + ", \"message\": \"" + message + "\", \"col\":\""+ col +"\",\"row\":\""+ row+"\"}");
    }
}

void OLEDLCD::drawText(String text, int textSize)
{
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
      print(text);
    }
    else
    {
      callOLEDLCDApi(OLEDLCDFunctions::OLEDDRAWTEXT, "{\"server_id\":"+String(getServerId()) + ", \"text\": \"" + text + "\", \"textSize\":"+ textSize +"}");
    }
}

void OLEDLCD::Clean(){
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
      lcd.clear();
    }
    else
    {
      callOLEDLCDApi(OLEDLCDFunctions::OLEDCLEAN, "{\"server_id\":"+String(getServerId()) + "}");
    }
}

int OLEDLCD::getAddress()
{
  return lcdAddress;
}

int OLEDLCD::getCol()
{
  return lcdColumns;
}

int OLEDLCD::getRows()
{
  return lcdRows;
}

#endif