#ifndef ELEVATORLOGTITLES_H
#define ELEVATORLOGTITLES_H

class ElevatorLogTitles
{    
public:
    //Database
    static const String ELEVATOR_BOOT;
    static const String ELEVATOR_INFO;
    static const String START_TO_CALIBRATE;
    static const String CALIBRATED;
    static const String SUMMON_BEFOR_CALIBRATING;
    static const String SUMMON_FLOOR;

};

const String ElevatorLogTitles::ELEVATOR_BOOT = "elevator_boot";
const String ElevatorLogTitles::ELEVATOR_INFO = "elevator_info";
const String ElevatorLogTitles::START_TO_CALIBRATE = "start_to_calibrate";
const String ElevatorLogTitles::CALIBRATED = "calibrated";
const String ElevatorLogTitles::SUMMON_BEFOR_CALIBRATING = "summon_befor_calibrating";
const String ElevatorLogTitles::SUMMON_FLOOR = "summon_floor";


#endif //ELEVATORLOGTITLES_H