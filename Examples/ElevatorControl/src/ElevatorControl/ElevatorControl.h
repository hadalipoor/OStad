#ifndef ELEVATORCONTROL_H
#define ELEVATORCONTROL_H

#include "IElevatorControl.h"
#include "../AppContext.h"
#include "../Config/DefaultElevatorControlConfigs.h"

class ElevatorControl : public IElevatorControl {
private:
    AppContext* context;

public:
    ElevatorControl(AppContext* context);
    
    void initialize() override;
    void update() override;
};

ElevatorControl::ElevatorControl(AppContext* context)
    : context(context) {}

void ElevatorControl::initialize() {

}

void ElevatorControl::update() {

}

#endif //ELEVATORCONTROL_H
