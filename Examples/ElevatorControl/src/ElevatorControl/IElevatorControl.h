#ifndef IELEVATORCONTROL
#define IELEVATORCONTROL

class IElevatorControl {
public:
    virtual void update() = 0;
    virtual void initialize() = 0;
};

#endif // IELEVATORCONTROL
