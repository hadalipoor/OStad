#include <OStad.h>
#include "cert.h"  // Include the certificate
#include "private_key.h"  // Include the private key

OStad* ostad;
void setup()
{
    Serial.begin(115200);
    LittleFS.begin(true);
    
    // CertificateData certificateData;
    // certificateData.certificate = const_cast<unsigned char*>(certificate);
    // certificateData.privatekey = const_cast<unsigned char*>(private_key);
    // certificateData.certificate_length = certificate_len;
    // certificateData.privateky_length = private_key_len;

    // ostad = new OStad(StorageType::SPIFFS_TYPE, certificateData);
    ostad = new OStad(StorageType::SPIFFS_TYPE);
    ostad->begin();
}

void loop()
{
    ostad->update();
}