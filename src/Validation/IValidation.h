// IValidation.h

#ifndef IVALIDATION_H
#define IVALIDATION_H

#include <string>

class IValidation {
public:
    virtual ~IValidation() {}

    virtual bool validateEmail(const String& email) = 0;
    virtual bool validateUsername(const String& username) = 0;
    virtual bool isColumnNameValid(const String& columnName) = 0;
    // Add more validation methods as needed
};

#endif // IVALIDATION_H
