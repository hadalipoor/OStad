
#ifndef DEFAULTDARBOON_H
#define DEFAULTDARBOON_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultDarboonConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultDarboonConfigs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in Darboon Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultDarboonConfigs::jsonString = R"(
{
    "system_enable" : "true",
    "rfid_enable" : "true",
    "wifi_open_door" : "true"
}
)";

#endif
