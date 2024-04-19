#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "IAuthentication.h"
#include "../AppContext.h"
#include "../Config/DefaultAuthenticationConfigs.h"

class Authentication : public IAuthentication {
private:
    AppContext* context;

public:
    Authentication(AppContext* context);
    
    void initialize() override;
    void update() override;
};

Authentication::Authentication(AppContext* context)
    : context(context) {}

void Authentication::initialize() {

}

void Authentication::update() {

}

#endif //AUTHENTICATION_H
