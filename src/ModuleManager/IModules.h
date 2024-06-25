#ifndef IMODULES_H
#define IMODULES_H

#include <string>
#include <PCF8574.h>
#include "Modules/IButton.h"
#include "Modules/IDHTSensor.h"
#include "Modules/IRelay.h"
#include "Modules/IRFIDPN.h"
#include "Modules/IRFID125Kh.h"
#include "Modules/IOLEDLCD.h"
#include "Modules/ILCD16X2.h"
#include "Modules/ISoilMoistureSensor.h"
#include "Modules/ModuleTypes.h"
#include "Modules/SimCardManager.h"

class IModules
{
public:
    virtual ~IModules() = default;

    virtual IButton* getButton(int server_id) = 0;
    // virtual IButton* getButton(int server_id, PCF8574* pcf8574) = 0;
    virtual int addButton(IButton* button) = 0;
    
    virtual int addDHTSensor(IDHTSensor* dhtSensor) = 0;
    virtual IDHTSensor* getDHTSensor(int server_id) = 0;

    virtual IRelay* getRelay(int server_id) = 0;
    virtual int addRelay(IRelay* relay) = 0;

    virtual IRFIDPN532* getRFIDPN532(int server_id) = 0;
    virtual int addRFIDPN532(IRFIDPN532* rfid) = 0;

    virtual IRFID125Kh* getRFID125Kh(int server_id) = 0;
    virtual int addRFID125Kh(IRFID125Kh* rfid) = 0;

    virtual ILCD16X2* getLCD16X2(int server_id) = 0;
    virtual int addLCD16X2(ILCD16X2* lcd16x2) = 0;
    
    virtual IOLEDLCD* getOLEDLCD(int server_id) = 0;
    virtual int addOLEDLCD(IOLEDLCD* oledlcd) = 0;
        
    virtual ISoilMoistureSensor* getSoilMoistureSensor(int server_id) = 0;
    virtual int addSoilMoistureSensor(ISoilMoistureSensor* soilMoistureSensor) = 0;
    
    virtual SimCardManager* getSimCardManager(int tx_pin, int rx_pin) = 0;

    virtual void initialize() = 0;
    virtual void update() = 0;
};

#endif // IMODULES_H
