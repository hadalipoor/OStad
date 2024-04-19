
#ifndef DEFAULTSABOORATANKER_H
#define DEFAULTSABOORATANKER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultSabooraTankerConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultSabooraTankerConfigs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in SabooraTanker Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultSabooraTankerConfigs::jsonString = R"(
{
    "system_enable" : "true"
}
)";

#endif
