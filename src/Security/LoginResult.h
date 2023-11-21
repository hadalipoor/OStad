#ifndef LOGINRESULT_H
#define LOGINRESULT_H

enum LoginResults
{
    AdminUser,
    Succesfull,
    NeedTwoFactorAuthentication,
    UsernameNotExists,
    PasswordIsIncorrect,
    WrongUserNameOrPassword,
    UserIsLocked,
    TowManyAttempts,
    WrongOTPCode,
    TwoFactorAuthenticationOtpCodeSent,
    TwoFactorAuthenticationOtpCodeNotSent,
    LogoutSuccessfull,
    LogoutUnSuccessfull,
    TokenNotSaved,
};

class LoginResult
{
private:
    
public:
    LoginResult();
    LoginResult(bool succesfull, LoginResults result);
    ~LoginResult();
    String getMessage();
    bool Succesfull;
    LoginResults Result;
    String Message;

};

LoginResult::LoginResult()
{

}

LoginResult::LoginResult(bool succesfull, LoginResults result): Succesfull(succesfull), Result(result), Message("")
{

}

LoginResult::~LoginResult()
{
}

String LoginResult::getMessage()
{
    if (Message != "")
    {
        return Message;
    }
    else
    {
        switch(Result)
        {
            case LoginResults::Succesfull:
                return "Login successful.";
            case LoginResults::NeedTwoFactorAuthentication:
                return "Two-factor authentication required.";
            case LoginResults::UsernameNotExists:
                return "Username does not exist.";
            case LoginResults::PasswordIsIncorrect:
                return "Password is incorrect.";
            case LoginResults::WrongUserNameOrPassword:
                return "Wrong username or password.";
            case LoginResults::UserIsLocked:
                return "User account is locked.";
            case LoginResults::TowManyAttempts:
                return "Too many login attempts.";
            case LoginResults::WrongOTPCode:
                return "OTP code is incorrect.";
            case LoginResults::TwoFactorAuthenticationOtpCodeSent:
                return "OTP code for two-factor authentication has been sent.";
            case LoginResults::TwoFactorAuthenticationOtpCodeNotSent:
                return "Failed to send OTP code for two-factor authentication.";
            case LoginResults::LogoutSuccessfull:
                return "Logout successful.";
            case LoginResults::LogoutUnSuccessfull:
                return "Logout unsuccessful.";
            case LoginResults::TokenNotSaved:
                return "Failed to save token.";
            default:
                return "Unknown result.";
        }
    }
}

#endif //LOGINRESULT_H