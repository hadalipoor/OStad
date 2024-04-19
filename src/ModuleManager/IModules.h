#ifndef IMODULES_H
#define IMODULES_H

#include <string>
#include <PCF8574.h>
#include "Modules/Button.h"
#include "Modules/DHTSensor.h"
#include "Modules/Relay.h"
#include "Modules/RFIDPN.h"
#include "Modules/RFID125Kh.h"
#include "Modules/OLEDLCD.h"
#include "Modules/LCD16X2.h"
#include "Modules/SoilMoistureSensor.h"
#include "Modules/ModuleTypes.h"
#include "Modules/SimCardManager.h"

class IModules
{
public:
    virtual ~IModules() = default;

    virtual Button* getButton(String name) = 0;
    virtual Button* getButton(String name, PCF8574* pcf8574) = 0;
    virtual int addButton(Button* button) = 0;
    
    virtual int addDHTSensor(DHTSensor* dhtSensor) = 0;
    virtual Button* getDHTSensor(String name) = 0;

    virtual Relay* getRelay(String name) = 0;
    virtual int addRelay(Relay* relay) = 0;

    virtual RFIDPN532* getRFIDPN532(String name) = 0;
    virtual int addRFIDPN532(RFIDPN532* rfid) = 0;

    virtual RFID125Kh* getRFID125Kh(String name) = 0;
    virtual int addRFID125Kh(RFID125Kh* rfid) = 0;

    virtual LCD16X2* getLCD16X2(String name) = 0;
    virtual int addLCD16X2(LCD16X2* lcd16x2) = 0;
    
    virtual OLEDLCD* getOLEDLCD(String name) = 0;
    virtual void addOLEDLCD(OLEDLCD* oledlcd) = 0;
        
    virtual SoilMoistureSensor* getSoilMoistureSensor(String name) = 0;
    virtual void addSoilMoistureSensor(SoilMoistureSensor* soilMoistureSensor) = 0;
    
    virtual SimCardManager* getSimCardManager(int tx_pin, int rx_pin) = 0;

    virtual void initialize() = 0;
};

#endif // IMODULES_H
