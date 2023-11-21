// Validation.h

#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include <regex>
#include "IValidation.h"

class Validation : public IValidation {
public:
    Validation()
    {
        
    }
    bool validateEmail(const String& email) override {
        // Implement email validation logic here.
        // For example, use a simple regex pattern:
        // std::regex emailPattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        // return std::regex_match(email, emailPattern);
        return true;
    }

    bool validateUsername(const String& username) override {
        // Implement username validation logic here.
        // For example, check if the username length is between 3 and 20 characters:
        return (username.length() >= 3 && username.length() <= 20);
    }

    bool isColumnNameValid(const String& columnName) override {
        // Implement column name validation logic here.
        // For example, check if the column name is "id" or "name":
        // return (columnName == "id" || columnName == "name");
        return true;
    }

    // Add more validation methods as needed
};

#endif // VALIDATION_H
