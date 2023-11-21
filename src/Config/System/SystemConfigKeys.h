#ifndef CONFIGKEYS_h
#define CONFIGKEYS_h

class SystemConfigKey
{
private:
    
public:
    static const String DB_CHANGE_INFO_SAVE;

    static const String WIFI_MODE_MESH;
    static const String WIFI_MODE_AP;
    static const String WIFI_MODE_WIFI;
    static const String AP_SSID;
    static const String AP_PASSWORD;
    static const String CHANNEL;
    static const String SSID_HIDDEN;
    static const String MAX_CONNECTION;
    static const String MESH_ROOT;
    static const String CLOCK_TYPE;
    static const String STORAGE_TYPE;
    static const String SD_PIN;
    static const String HTTPS_ENABLE;
    static const String DEFAULT_USERNAME;
    static const String DEFAULT_PASSWORD;
    static const String SERIAL_PRINT_ENABLE;
};

//Database keys
const String SystemConfigKey::DB_CHANGE_INFO_SAVE = "db_change_info_save";


//Network keys
const String SystemConfigKey::WIFI_MODE_MESH = "wifi_mode_mesh";
const String SystemConfigKey::WIFI_MODE_AP = "wifi_mode_ap";
const String SystemConfigKey::WIFI_MODE_WIFI = "wifi_mode_wifi";
const String SystemConfigKey::AP_SSID = "ap_ssid";
const String SystemConfigKey::AP_PASSWORD = "ap_password";
const String SystemConfigKey::CHANNEL = "channel";
const String SystemConfigKey::SSID_HIDDEN = "ssid_hidden";
const String SystemConfigKey::MAX_CONNECTION = "max_connection";
const String SystemConfigKey::MESH_ROOT = "mesh_root";
const String SystemConfigKey::CLOCK_TYPE = "clock_type";
const String SystemConfigKey::STORAGE_TYPE = "storage_type";
const String SystemConfigKey::SD_PIN = "sd_pin";
const String SystemConfigKey::HTTPS_ENABLE = "https_enable";
const String SystemConfigKey::DEFAULT_USERNAME = "default_username";
const String SystemConfigKey::DEFAULT_PASSWORD = "default_password";
const String SystemConfigKey::SERIAL_PRINT_ENABLE = "serial_print_enable";

#endif