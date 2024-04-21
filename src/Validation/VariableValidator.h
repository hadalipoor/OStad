#ifndef VARIABLEVALIDATOR_H
#define VARIABLEVALIDATOR_H

#include "../Clock/EBPDateTime.h"

class VariableValidator
{
public:
    VariableValidator();
    static bool isNumber(String str);
    static bool isDateTime(String str);
};

VariableValidator::VariableValidator()
{

}

bool VariableValidator::isNumber(String str)
{
    for(byte i=0;i<str.length();i++)
    {
        if(isDigit(str.charAt(i))) return true;
    }
    return false;   
}

bool VariableValidator::isDateTime(String str)
{
    return EBPDateTime().isDateTimeStringValid(str);
}

#endif //VARIABLEVALIDATOR_H