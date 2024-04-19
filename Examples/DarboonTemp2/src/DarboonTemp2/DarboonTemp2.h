#ifndef DARBOONTEMP2_H
#define DARBOONTEMP2_H

#include "IDarboonTemp2.h"
#include "../AppContext.h"
#include "../Config/DefaultDarboonTemp2Configs.h"

class DarboonTemp2 : public IDarboonTemp2 {
private:
    AppContext* context;

public:
    DarboonTemp2(AppContext* context);
    
    void initialize() override;
    void update() override;
};

DarboonTemp2::DarboonTemp2(AppContext* context)
    : context(context) {}

void DarboonTemp2::initialize() {

}

void DarboonTemp2::update() {

}

#endif //DARBOONTEMP2_H
