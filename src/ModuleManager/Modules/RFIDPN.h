#ifndef RFIDPN532_H
#define RFIDPN532_H

#include <SPI.h>
#include "../Tools/PN532_SPI/PN532_SPI.h"
#include "../Tools/PN532/PN532.h"
#include "ModuleTypes.h"
#include "../../Database/Entities/Modules/RFIDFullEntity.h"

class RFIDPN532
{
public:
    using RFIDCallback = std::function<void(String)>;
private:
    PN532_SPI* pn532spi;
    PN532* nfc;
    RFIDCallback onNewTag;

public:
    RFIDPN532(uint8_t ssPin, String name);
    void setOnNewTag(RFIDCallback function);
    bool checkModule();
    uint32_t getVersionData();
    RFIDFullEntity* getEntity();
    void update();
    ~RFIDPN532();
    
    String name;
    int ss_pin;
    String connectionType;
    int nodeId;
};

RFIDPN532::RFIDPN532(uint8_t ssPin, String name): name(name),ss_pin(ssPin), connectionType("")/*FIX IT*/, nodeId(0) 
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
    
  Serial.println("Waiting for an ISO14443A card");
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

RFIDFullEntity* RFIDPN532::getEntity()
{
    return new RFIDFullEntity(0, 0, name, ModuleTypes::RFIDPN532, connectionType, nodeId, ss_pin);
}

RFIDPN532::~RFIDPN532()
{
}
#endif