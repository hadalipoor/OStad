#ifndef RFIDPN532_H
#define RFIDPN532_H

#include <SPI.h>
#include "../Tools/PN532_SPI/PN532_SPI.h"
#include "../Tools/PN532/PN532.h"
#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/RFIDFullEntity.h"
#include "../../Context.h"
#include "IRFIDPN.h"

class RFIDPN532: public IRFIDPN532
{
private:
    PN532_SPI* pn532spi;
    PN532* nfc;
    RFIDCallback onNewTag;
    Context* context;
    int ss_pin;
    String ip;
    String protocolType;

public:
    RFIDPN532(Context* context, uint8_t ssPin, int module_id, int server_id, String name, String moduleType, int device_id);
    void setOnNewTag(RFIDCallback function);
    bool checkModule();
    uint32_t getVersionData();
    RFIDFullEntity* getEntity();
    void update();
    int getSSPin();
    ~RFIDPN532();
    
};

RFIDPN532::RFIDPN532(Context* context, uint8_t ssPin, int module_id, int server_id, String name, String moduleType, int device_id): 
    IRFIDPN532(module_id, server_id, name, moduleType, device_id), ss_pin(ssPin), context(context)
{
    if(device_id == context->getDeviceManager()->deviceId)
    {
        onNewTag = nullptr;
        pn532spi = new PN532_SPI(SPI, 22);
        nfc = new PN532(*pn532spi);
        nfc->begin();
        if (!checkModule())
        {
            return;
        }
        
    
        // Set the max number of retry attempts to read from a card
        // This prevents us from waiting forever for a card, which is
        // the default behaviour of the PN532.
        nfc->setPassiveActivationRetries(0xFF);
        
        // configure board to read RFID tags
        nfc->SAMConfig();
    }
    else
    {
        protocolType = context->getConfig()->getDeviceConfig()->get(DeviceConfigKeys::PROTOCOL_TYPE);
        ModulesController* modulesController = new ModulesController(context, storageType);
        RFIDFullEntity* rfidFullEntity = modulesController->getRFIDByServerId(getServerId());
        int deviceId = rfidFullEntity->DeviceId;
        DevicesController* devicesController = new DevicesController(context, storageType);
        DevicesEntity device = devicesController->GetById(deviceId);
        ip = device.getIP();
    }
}

void RFIDPN532::setOnNewTag(RFIDCallback function)
{
    onNewTag = function;
}

bool RFIDPN532::checkModule()
{
    uint32_t versiondata = getVersionData();
    if (! versiondata) {
        Serial.print("Didn't find PN53x board");
        return false;
    }
    
    // Got ok data, print it out!
    Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
    // Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
    // Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
    return true;
  
}

uint32_t RFIDPN532::getVersionData()
{
    return nfc->getFirmwareVersion();
}

void RFIDPN532::update()
{
    if(getDeviceID() == context->getDeviceManager()->deviceId)
    {
        boolean success;
        uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
        uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
        String Str_uid;

        // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
        // 'uid' will be populated with the UID, and uidLength will indicate
        // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
        success = nfc->readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

        if (success) {
        Serial.println("Found a card!");
        // Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
        // Serial.print("UID Value: ");
        for (uint8_t i=0; i < uidLength; i++) 
        {
            Str_uid += String(uid[i]);
            Serial.print(" 0x");Serial.print(uid[i], HEX); 
        }
        if (onNewTag == nullptr)
        {
            // Serial.print("OnNewTag is null");
            return;
        }
        // Serial.print("OnNewTag is not null!!!!");

        onNewTag(Str_uid);
        Str_uid = "";
        // Wait 1 second before continuing
        // delay(1000);
        }
    }
}

int RFIDPN532::getSSPin()
{
    return ss_pin;
}

RFIDFullEntity* RFIDPN532::getEntity()
{
    return new RFIDFullEntity(0, getModuleID(),getName(), getSSPin(), getDeviceID(), getServerId());
}

RFIDPN532::~RFIDPN532()
{
}
#endif