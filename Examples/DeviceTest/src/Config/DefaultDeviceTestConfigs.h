
#ifndef DEFAULTDEVICETEST_H
#define DEFAULTDEVICETEST_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultDeviceTestConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultDeviceTestConfigs::get(String key) {
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

const String DefaultDeviceTestConfigs::jsonString = R"(
{
    "device_type" : "server",
    "chip_id" : "",
    "device_name" : "OStad Server",
    "" : ""
}
)";

#endif
