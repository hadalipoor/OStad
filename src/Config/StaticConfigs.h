#ifndef STATICCONFIGS_H
#define STATICCONFIGS_H

#include <Arduino.h>

class StaticConfigs {
public:
    // Database configuration
    static constexpr const char* DATABASE_PATH = "/";

    // Serial communication configuration
    static constexpr long SERIAL_BAUD_RATE = 115200;

    // Wi-Fi configuration
    static constexpr const char* AP_SSID = "your_ssid";
    static constexpr const char* AP_PASSWORD = "your_password";

    // Web server configuration
    static constexpr uint16_t WEB_SERVER_PORT = 80;

    // Other configurations can be added as needed
};

#endif
