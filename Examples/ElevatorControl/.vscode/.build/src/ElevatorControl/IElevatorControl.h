#ifndef IELEVATORCONTROL
#define IELEVATORCONTROL

enum MovementState{
  CALIBRATING,
  MOVE_UP,
  MOVE_DOWN,
  STOP,
  EMERGENCY_STOP,
  WAITING,
  NONE
};

enum MovementMethod{
  MANUAL,
  AUTOMATIC
};

enum CalibrationSensorPosition { TOP, BOTTOM };

enum ElevatorMode {SINGLE_SENSOR, SEPARATE_SENSORS};

class IElevatorControl {
public:
    virtual void update() = 0;
    virtual void initialize() = 0;
    virtual void setMovementMethod(MovementMethod movementMethod) = 0;
    virtual MovementMethod getMovementMethod() = 0;
    virtual void setElevatorMode(ElevatorMode elevatorMode) = 0;
    virtual ElevatorMode getElevatorMode() = 0;
    virtual void MoveUpManual() = 0;
    virtual String CalibrationRequested() = 0;
    virtual void MoveDownManual() = 0;
    virtual void StopManual() = 0;
    virtual MovementState getState() = 0;
    virtual String FloorRequested(int floor) = 0;
    virtual String EMSStopRequested() = 0;
    virtual String RequestCalibration() = 0;
    virtual int GetCurrentFLoor() = 0;
    virtual String getLCDMessagePersian() = 0;
    virtual String getLCDMessage() = 0;
};

#endif // IELEVATORCONTROL
