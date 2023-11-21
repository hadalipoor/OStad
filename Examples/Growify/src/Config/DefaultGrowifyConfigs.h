
#ifndef DEFAULTGROWIFY_H
#define DEFAULTGROWIFY_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultGrowifyConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultGrowifyConfigs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in Growify Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultGrowifyConfigs::jsonString = R"(
{
    "system_enable" : "true",
    "polling_interval" : "5",
    "data_aggregation_interval" : "60",
    "alert_threshold_temperature" : "30",
    "alert_threshold_humidity" : "70",
    "alert_threshold_light" : "800",
    "alert_threshold_soil_moisture" : "40",
    "SMS_alerts_enable" : "false",
    "SMS_message_temperature" : "Warning! Temperature is outside of the defined threshold.",
    "SMS_message_humidity" : "Warning! Humidity is outside of the defined threshold.",
    "SMS_message_light" : "Warning! Light intensity is outside of the defined threshold.",
    "SMS_message_soil_moisture" : "Warning! Soil moisture is outside of the defined threshold.",
    "SMS_alerts_number" : "",
    "database_size_limit" : "1000",
    "automatic_updates_enable" : "true",
    "automatic_updates_interval" : "168",
    "automatic_condition_adjustments_enable" : "true"
}
)";

#endif
