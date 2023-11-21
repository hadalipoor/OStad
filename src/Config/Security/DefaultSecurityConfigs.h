
#ifndef DEFAULTAUTHENTICATION_H
#define DEFAULTAUTHENTICATION_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultSecurityConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultSecurityConfigs::get(String key) {
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        Serial.println(jsonString);
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in Security Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultSecurityConfigs::jsonString = R"(
{
    "authentication_enable" : "false",
    "2fa_enable" : "false",
    "2fa_email_enable" : "false",
    "2fa_sms_enable" : "false",
    "access_with_api_key" : "true",
    "rst_pswd_with_sms" : "false",
    "rst_pswd_with_email" : "false",
    "rst_pswd_with_button" : "true",
    "rst_pswd_by_sec_qustn" : "true",
    "rst_pswd_expire_hour" : "24",
    "login_attempt_count" : "10",
    "lock_user_login_attempt" : "false",
    "lock_user_minute" : "30",
    "two_factor_auth_expire_hour" : "24",
    "log_account_activity" : "true",
    "token_active_day" : "5"
}
)";

#endif
