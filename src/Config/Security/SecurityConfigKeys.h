
#ifndef AUTHENTICATIONCONFIGKEYS_H
#define AUTHENTICATIONCONFIGKEYS_H

class SecurityConfigKey
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
    static const String TOKEN_ACTIVE_DAY;
    static const String TWO_FACTOR_AUTH_EXPIRE_HOUR;
    static const String LOG_ACCOUNT_ACTIVITY;
};

const String SecurityConfigKey::AUTHENTICATION_ENABLE = "authentication_enable";
const String SecurityConfigKey::TWO_FACTOR_AUTHENTICATION_ENABLE = "2fa_enable";
const String SecurityConfigKey::TWO_FACTOR_AUTHENTICATION_EMAIL_ENABLE = "2fa_email_enable";
const String SecurityConfigKey::TWO_FACTOR_AUTHENTICATION_SMS_ENABLE = "2fa_sms_enable";
const String SecurityConfigKey::ACCESS_WITH_API_KEY = "access_with_api_key";
const String SecurityConfigKey::RESET_PASSWORD_WITH_SMS = "rst_pswd_with_sms";
const String SecurityConfigKey::RESET_PASSWORD_WITH_EMAIL = "rst_pswd_with_email";
const String SecurityConfigKey::RESET_PASSWORD_WITH_BUTTON = "rst_pswd_with_button";
const String SecurityConfigKey::RESET_PASSWORD_WITH_SECURITY_QUESTION = "rst_pswd_by_sec_qustn";
const String SecurityConfigKey::RESET_PASSWORD_EXPIRE_HOUR = "rst_pswd_expire_hour";
const String SecurityConfigKey::LOGIN_ATTEMPT_COUNT = "login_attempt_count";
const String SecurityConfigKey::LOCK_USER_LOGIN_ATTEMPT = "lock_user_login_attempt";
const String SecurityConfigKey::LOCK_USER_MINUTE = "lock_user_minute";
const String SecurityConfigKey::TWO_FACTOR_AUTH_EXPIRE_HOUR = "two_factor_auth_expire_hour";
const String SecurityConfigKey::LOG_ACCOUNT_ACTIVITY = "log_account_activity";
const String SecurityConfigKey::TOKEN_ACTIVE_DAY = "token_active_day";

#endif // AUTHENTICATIONCONFIGKEYS_H
