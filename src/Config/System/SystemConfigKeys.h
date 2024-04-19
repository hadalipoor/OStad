#ifndef CONFIGKEYS_h
#define CONFIGKEYS_h

class SystemConfigKey
{
private:
    
public:
    static const String DB_CHANGE_INFO_SAVE;
    static const String CLOCK_TYPE;
    static const String SYNC_CLOCK;

    static const String WIFI_MODE_MESH;
    static const String WIFI_MODE_AP;
    static const String WIFI_MODE_WIFI;
    static const String AP_SSID;
    static const String AP_PASSWORD;
    static const String CHANNEL;
    static const String SSID_HIDDEN;
    static const String MAX_CONNECTION;
    static const String MESH_ROOT;
    static const String STORAGE_TYPE;
    static const String SD_PIN;
    static const String HTTPS_ENABLE;
    static const String DEFAULT_USERNAME;
    static const String DEFAULT_PASSWORD;
    static const String SERIAL_PRINT_ENABLE;
    static const String DEFAULT_IP;
    static const String DEFAULT_GATEWAY;
    static const String DEFAULT_SUBNET;
    static const String DEFAULT_PRIMARYDNS;
    static const String DEFAULT_SECONDARYDNS;
};

//Database keys
const String SystemConfigKey::DB_CHANGE_INFO_SAVE = "db_change_info_save";

const String SystemConfigKey::CLOCK_TYPE = "clock_type";
const String SystemConfigKey::SYNC_CLOCK = "sync_clock";

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
const String SystemConfigKey::STORAGE_TYPE = "storage_type";
const String SystemConfigKey::SD_PIN = "sd_pin";
const String SystemConfigKey::HTTPS_ENABLE = "https_enable";
const String SystemConfigKey::DEFAULT_USERNAME = "default_username";
const String SystemConfigKey::DEFAULT_PASSWORD = "default_password";
const String SystemConfigKey::SERIAL_PRINT_ENABLE = "serial_print_enable";
const String SystemConfigKey::DEFAULT_IP = "default_ip";
const String SystemConfigKey::DEFAULT_SUBNET = "default_subnet";
const String SystemConfigKey::DEFAULT_GATEWAY = "default_gateway";
const String SystemConfigKey::DEFAULT_PRIMARYDNS = "default_primaryDNS";
const String SystemConfigKey::DEFAULT_SECONDARYDNS = "secondaryDNS";

#endif