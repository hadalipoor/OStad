// IValidation.h

#ifndef IVALIDATION_H
#define IVALIDATION_H

#include "VariableValidator.h"

class IValidation {
public:
    virtual ~IValidation() {}

    virtual VariableValidator* variableValidator() = 0;
};

#endif // IVALIDATION_H
