
#ifndef AUTHENTICATIONCONFIGKEYS_H
#define AUTHENTICATIONCONFIGKEYS_H

class AuthenticationConfigKey
{
private:

public:
    static const String AUTHENTICATION_ENABLE;
    static const String TWO_FACTOR_AUTHENTICATION_ENABLE;
    static const String TWO_FACTOR_AUTHENTICATION_EMAIL_ENABLE;
    static const String TWO_FACTOR_AUTHENTICATION_SMS_ENABLE;
    static const String ACCESS_WITH_API_KEY;
    static const String RESET_PASSWORD_WITH_SMS;
    static const String RESET_PASSWORD_WITH_EMAIL;
    static const String RESET_PASSWORD_WITH_BUTTON;
    static const String RESET_PASSWORD_WITH_SECURITY_QUESTION;
    static const String RESET_PASSWORD_EXPIRE_HOUR;
    static const String LOGIN_ATTEMPT_COUNT;
    static const String LOCK_USER_LOGIN_ATTEMPT;
    static const String LOCK_USER_MINUTE;
    static const String TWO_FACTOR_AUTH_EXPIRE_HOUR;
    static const String LOG_ACCOUNT_ACTIVITY;
};

const String AuthenticationConfigKey::AUTHENTICATION_ENABLE = "authentication_enable";
const String AuthenticationConfigKey::TWO_FACTOR_AUTHENTICATION_ENABLE = "two_factor_authentication_enable";
const String AuthenticationConfigKey::TWO_FACTOR_AUTHENTICATION_EMAIL_ENABLE = "two_factor_authentication_email_enable";
const String AuthenticationConfigKey::TWO_FACTOR_AUTHENTICATION_SMS_ENABLE = "two_factor_authentication_sms_enable";
const String AuthenticationConfigKey::ACCESS_WITH_API_KEY = "access_with_api_key";
const String AuthenticationConfigKey::RESET_PASSWORD_WITH_SMS = "reset_password_with_sms";
const String AuthenticationConfigKey::RESET_PASSWORD_WITH_EMAIL = "reset_password_with_email";
const String AuthenticationConfigKey::RESET_PASSWORD_WITH_BUTTON = "reset_password_with_button";
const String AuthenticationConfigKey::RESET_PASSWORD_WITH_SECURITY_QUESTION = "reset_password_with_security_question";
const String AuthenticationConfigKey::RESET_PASSWORD_EXPIRE_HOUR = "reset_password_expire_hour";
const String AuthenticationConfigKey::LOGIN_ATTEMPT_COUNT = "login_attempt_count";
const String AuthenticationConfigKey::LOCK_USER_LOGIN_ATTEMPT = "lock_user_login_attempt";
const String AuthenticationConfigKey::LOCK_USER_MINUTE = "lock_user_minute";
const String AuthenticationConfigKey::TWO_FACTOR_AUTH_EXPIRE_HOUR = "two_factor_auth_expire_hour";
const String AuthenticationConfigKey::LOG_ACCOUNT_ACTIVITY = "log_account_activity";

#endif // AUTHENTICATIONCONFIGKEYS_H
