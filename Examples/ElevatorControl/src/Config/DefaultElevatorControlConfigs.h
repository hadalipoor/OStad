
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
    StaticJsonDocument<1024> doc;
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
    "elevator_enable" : "true",
    "elevator_mode" : "single_sensor",
    "emergency_button_enabled" : "true",
    "manual_move_up_milis" : "50",
    "manual_move_down_milis" : "50",

    "calibration_on_startup" : "false",
    "calibration_sensor_with_floor" : "false",
    "calibration_sensor_position" : "top",
    "calibration_sensor_interval" : "60",
    "calibration_direction" : "top",
    "parking_floor" : "1",
    
    "relay_start_delay" : "500",
    "number_of_floors" : "5",
    "send_error_data" : "true",
    
    "admin_phone_number" : "",
    "floor_sensor_interval" : "5",

    "elevator_max_capacity" : "10"
}
)";

#endif
