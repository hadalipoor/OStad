
#ifndef ELEVATORCONTROLCONFIGKEYS_H
#define ELEVATORCONTROLCONFIGKEYS_H

class ElevatorControlConfigKey
{
private:

public:
    static const String ELEVATOR_ENABLE;
    static const String ELEVATOR_MODE;
    static const String MANUAL_MOVE_UP_MILIS;
    static const String MANUAL_MOVE_DOWN_MILIS;
    static const String ELEVATOR_MAX_CAPACITY;
    static const String EMERGENCY_BUTTON_ENABLED;
    static const String FLOOR_SENSOR_INTERVAL;
    static const String CALIBRATION_SENSOR_INTERVAL;
    static const String PARKING_FLOOR;
    static const String CALIBRATION_DIRECTION;
    static const String RELAY_START_DELAY;
    static const String NUMBER_OF_FLOORS;
    static const String CALIBRATION_SENSOR_POSITION;
    static const String ADMIN_PHONE_NUMBER;
    static const String SEND_ERROR_DATA;
    static const String CALIBRATION_ON_STARTUP;
    static const String CALIBRATION_SENSOR_WITH_FLOOR;
};

const String ElevatorControlConfigKey::ELEVATOR_ENABLE = "elevator_enable";
const String ElevatorControlConfigKey::ELEVATOR_MODE = "elevator_mode";
const String ElevatorControlConfigKey::ELEVATOR_MAX_CAPACITY = "elevator_max_capacity";
const String ElevatorControlConfigKey::MANUAL_MOVE_UP_MILIS = "manual_move_up_milis";
const String ElevatorControlConfigKey::MANUAL_MOVE_DOWN_MILIS = "manual_move_down_milis";
const String ElevatorControlConfigKey::EMERGENCY_BUTTON_ENABLED = "emergency_button_enabled";
const String ElevatorControlConfigKey::FLOOR_SENSOR_INTERVAL = "floor_sensor_interval";
const String ElevatorControlConfigKey::CALIBRATION_SENSOR_INTERVAL = "calibration_sensor_interval";
const String ElevatorControlConfigKey::PARKING_FLOOR = "parking_floor";
const String ElevatorControlConfigKey::CALIBRATION_DIRECTION = "calibration_direction";
const String ElevatorControlConfigKey::RELAY_START_DELAY = "relay_start_delay";
const String ElevatorControlConfigKey::NUMBER_OF_FLOORS = "number_of_floors";
const String ElevatorControlConfigKey::CALIBRATION_SENSOR_POSITION = "calibration_sensor_position";
const String ElevatorControlConfigKey::ADMIN_PHONE_NUMBER = "admin_phone_number";
const String ElevatorControlConfigKey::SEND_ERROR_DATA = "send_error_data";
const String ElevatorControlConfigKey::CALIBRATION_ON_STARTUP = "calibration_on_startup";
const String ElevatorControlConfigKey::CALIBRATION_SENSOR_WITH_FLOOR = "calibration_sensor_with_floor";

#endif // ELEVATORCONTROLCONFIGKEYS_H
