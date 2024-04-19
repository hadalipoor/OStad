#ifndef DEFAULTCONFIGS_H
#define DEFAULTCONFIGS_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultSystemConfigs {
  public:
    static const String jsonString;

    static String get(String key);
};

String DefaultSystemConfigs::get(String key) {
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
    Serial.println(F("Failed to parse jsonString"));Serial.println(key);
    return "";
    }

    if (doc.containsKey(key)) {
    return String(doc[key].as<const char *>());
    } else {
    return "";
    }
}
const String DefaultSystemConfigs::jsonString = R"(
{
    "db_change_info_save" : "false",
    "system_boot_info_save" : "true",
    "clock_type" : "Internal",
    "sync_clock" : "false",
    "relay_state_changed_info_save" : "true",
    "wifi_mode_mesh" : "false",
    "wifi_mode_ap" : "true",
    "wifi_mode_wifi" : "false",
    "ap_ssid" : "OStad AP",
    "ap_password" : "12345678",
    "channel" : "1",
    "ssid_hidden" : "false",
    "max_connection" : "6",
    "mesh_root" : "false",
    "storage_type" : "SPIFFS_TYPE",
    "sd_pin" : "26",
    "https_enable" : "true",
    "default_username" : "admin",
    "default_password" : "admin",
    "serial_print_enable" : "true",
    "default_ip": "",
    "default_gateway": "",
    "default_subnet": "",
    "default_primaryDNS": "",
    "default_secondaryDNS": ""
}
)";

#endif