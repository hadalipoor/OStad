#ifndef GROWIFY_H
#define GROWIFY_H

#include "IGrowify.h"
#include "../AppContext.h"
#include "../Config/DefaultGrowifyConfigs.h"

class Growify : public IGrowify {
private:
    AppContext* context;

public:
    Growify(AppContext* context);
    
    void initialize() override;
    void update() override;
};

Growify::Growify(AppContext* context)
    : context(context) {}

void Growify::initialize() {

}

void Growify::update() {

}

#endif //GROWIFY_H
