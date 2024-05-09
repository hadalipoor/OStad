
#ifndef DEFAULTDEVICEVALUE_H
#define DEFAULTDEVICEVALUE_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultDeviceConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultDeviceConfigs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in DeviceTest Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultDeviceConfigs::jsonString = R"(
{
    "device_type" : "server",
    "chip_id" : "",
    "device_name" : "OStad Server",
    "Protocol_type": "http"
}
)";

#endif
