#ifndef IVALIDATION_H
#define IVALIDATION_H

#include "VariableValidator.h"
#include "NetworkValidator.h"

class IValidation {
public:
    virtual ~IValidation() {}

    virtual VariableValidator* variableValidator() = 0;
    virtual NetworkValidator* networkValidator() = 0;
};

#endif // IVALIDATION_H
