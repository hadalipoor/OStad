#define LOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO
#define LOG_LEVEL_WARNING
#define LOG_LEVEL_ERROR
// #define OSTAD_NETWORK_ENABLE

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
    
    ostad->getContext()->getLogger()->log(
        LogLevel::INFO_LEVEL, LogTitles::USER_LOGS, ostad->getContext()->getConfig()->getSystemConfig()->get(SystemConfigKey::WIFI_MODE_WIFI));
    
    ostad->getContext()->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::USER_LOGS, "this log will store in local log table.");

    
    ostad->getContext()->getNetwork()->addApi(new ResourceNode("/testapi", LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        response(res, "Hello World");
    }));
}

void loop()
{
    ostad->update();
}