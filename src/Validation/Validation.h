// Validation.h

#ifndef VALIDATION_H
#define VALIDATION_H

#include "../Context.h"
#include "IValidation.h"

class Validation : public IValidation {
private:
    Context* context;
public:
    Validation();
    Validation(Context* cntxt);
    
    VariableValidator* variableValidator() override;
};

Validation::Validation(Context* cntxt): context(cntxt)
{
    
}

Validation::Validation()
{
    
}

VariableValidator* Validation::variableValidator()
{
    return new VariableValidator();
}

#endif // VALIDATION_H
