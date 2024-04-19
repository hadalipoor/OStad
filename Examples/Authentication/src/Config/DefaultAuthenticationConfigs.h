
#ifndef DEFAULTAUTHENTICATION_H
#define DEFAULTAUTHENTICATION_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultAuthenticationConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultAuthenticationConfigs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in Authentication Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultAuthenticationConfigs::jsonString = R"(
{
    "authentication_enable" : "true",
    "two_factor_authentication_enable" : "false",
    "two_factor_authentication_email_enable" : "false",
    "two_factor_authentication_sms_enable" : "false",
    "access_with_api_key" : "true",
    "reset_password_with_sms" : "false",
    "reset_password_with_email" : "false",
    "reset_password_with_button" : "true",
    "reset_password_with_security_question" : "true",
    "reset_password_expire_hour" : "24",
    "login_attempt_count" : "10",
    "lock_user_login_attempt" : "false",
    "lock_user_minute" : "30",
    "two_factor_auth_expire_hour" : "24",
    "log_account_activity" : "true"
}
)";

#endif
