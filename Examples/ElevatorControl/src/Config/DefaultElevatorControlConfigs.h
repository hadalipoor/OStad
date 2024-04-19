
#ifndef DEFAULTELEVATORCONTROL_H
#define DEFAULTELEVATORCONTROL_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultElevatorControlConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultElevatorControlConfigs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in ElevatorControl Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultElevatorControlConfigs::jsonString = R"(
{
    "elevator_max_capacity" : "10",
    "emergency_button_enabled" : "true",
    "floor_sensor_interval" : "5",
    "calibration_sensor_interval" : "60",
    "parking_floor" : "1",
    "wait_time" : "500",
    "relay_start_delay" : "500",
    "number_of_floors" : "5",
    "calibration_sensor_position" : "top",
    "admin_phone_number" : "",
    "send_error_data" : "true",
    "calibration_on_startup" : "false",
    "calibration_sensor_with_floor" : "false"
}
)";

#endif
