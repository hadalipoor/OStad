
#ifndef DEFAULTSABOORAHUB2_H
#define DEFAULTSABOORAHUB2_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultSabooraHub2Configs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultSabooraHub2Configs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in SabooraHub2 Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultSabooraHub2Configs::jsonString = R"(
{
    "system_enable" : "true",
    "rfid_enable" : "true",
    "wifi_open_door" : "true"
}
)";

#endif
