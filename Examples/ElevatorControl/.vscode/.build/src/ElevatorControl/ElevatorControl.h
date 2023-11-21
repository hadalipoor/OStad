#ifndef ELEVATORCONTROL_H
#define ELEVATORCONTROL_H

#include "IElevatorControl.h"
#include "../AppContext.h"
#include "../Config/DefaultElevatorControlConfigs.h"
#include "../Config/ElevatorControlConfigKeys.h"
#include "../Log/ElevatorLogTitle.h"
#include "../DeviceManager/SevenSegment.h"


class ElevatorControl : public IElevatorControl {
private:
    AppContext* context;
    std::vector<Button*> floorButtons; // added floorButtons vector

    MovementState movementState;
    MovementMethod _movementMethod;
    ElevatorMode _elevatorMode;
    CalibrationSensorPosition calibrationPosition;


    int _currentLocation;

    int currentFloor;
    int parkingFloor;
    std::vector<int> floorQueue;
    unsigned long waitTime;
    unsigned long relayStartDelay;
    bool isElevatorEnable;
    int numberOfFloors;
    String emergency_button_enabled;
    bool isCalibrationSensorWithFloorSensor;
    bool calibrating;
    bool isCalibrated;
    bool calibration_on_strtup;
    CalibrationSensorPosition calibration_direction;
    int floor_sensor_interval;
    PCF8574* pcf8574;
    SevenSegment* display;


    bool isInt(String str);
    void MoveUp();
    void MoveDown();
    void Stop(bool changeState);
    void handleCurrentFloor();
    void handleIncomingMessage(String phoneNumber, String message);
public:
    ElevatorControl(AppContext* context);
    
    void initialize() override;
    void moveToNextFloor();
    void summonFloor(int floor);
    void update() override;
    void EMSStop();
    void MoveUpManual() override;
    void MoveDownManual() override;
    void StopManual() override;
    String FloorRequested(int floor) override;
    String CalibrationRequested() override;
    void CalibrationSensorClicked(Button* button);
    void setElevatorMode(ElevatorMode elevatorMode) override;
    ElevatorMode getElevatorMode() override;
    String EMSStopRequested() override;
    String RequestCalibration() override;
    void OnFloorSensorClicked(int floor);
    void setMovementMethod(MovementMethod movementMethod) override;
    MovementMethod getMovementMethod() override;
    MovementState getState() override;
    int GetCurrentFLoor() override;
    String getLCDMessagePersian() override;
    String getLCDMessage() override;
};

ElevatorControl::ElevatorControl(AppContext* context)
    : context(context), emergency_button_enabled(true), 
            floor_sensor_interval(0), isElevatorEnable(true), _elevatorMode(ElevatorMode::SEPARATE_SENSORS), calibration_on_strtup(false)
            ,isCalibrated(false) {}

void ElevatorControl::initialize()
{
    pcf8574 = new PCF8574(0x20);
    display = new SevenSegment(*pcf8574);
    display->begin();

    floorQueue = std::vector<int>();
    
    movementState = MovementState::STOP;
    _movementMethod = MovementMethod::AUTOMATIC;

    currentFloor = 0;
    String isElevatorEnableStr = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::ELEVATOR_ENABLE);
    if (isElevatorEnableStr == "true")
    {
        isElevatorEnable = true;
    }
    else if (isElevatorEnableStr == "false")
    {
        isElevatorEnable = false;
    }

    String calibrationPositionStr = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::CALIBRATION_SENSOR_POSITION);
    if (calibrationPositionStr == "top")
    {
        calibrationPosition = CalibrationSensorPosition::TOP;
    }
    else
    {
        calibrationPosition = CalibrationSensorPosition::BOTTOM;
    }
    
    String calibrationDirectionStr = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::CALIBRATION_DIRECTION);
    if (calibrationDirectionStr == "top")
    {
        calibration_direction = CalibrationSensorPosition::TOP;
    }
    else
    {
        calibration_direction = CalibrationSensorPosition::BOTTOM;
    }

    String elevatorModeStr = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::ELEVATOR_MODE);
    if (elevatorModeStr == "single_sensor")
    {
        _elevatorMode = ElevatorMode::SINGLE_SENSOR;
    }
    else if (elevatorModeStr == "separate_sensors")
    {
        _elevatorMode = ElevatorMode::SEPARATE_SENSORS;
    }

    String isCalibrationSensorWithFloorSensorStr = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::CALIBRATION_SENSOR_WITH_FLOOR);
    if (isCalibrationSensorWithFloorSensorStr == "true")
    {
        isCalibrationSensorWithFloorSensor = true;
    }
    else if (isCalibrationSensorWithFloorSensorStr == "false")
    {
        isCalibrationSensorWithFloorSensor = false;
    }

    String calibration_on_strtupStr = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::CALIBRATION_ON_STARTUP);
    if (calibration_on_strtupStr == "true")
    {
        calibration_on_strtup = true;
    }
    else if (calibration_on_strtupStr == "false")
    {
        calibration_on_strtup = false;
    }
    

    parkingFloor = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::PARKING_FLOOR).toInt();
    waitTime = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::CALIBRATION_DIRECTION).toInt();
    relayStartDelay = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::RELAY_START_DELAY).toInt();
    floor_sensor_interval = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::FLOOR_SENSOR_INTERVAL).toInt();
    emergency_button_enabled = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::EMERGENCY_BUTTON_ENABLED);
    calibrating = false;
    
    numberOfFloors = context->getElevatorControlConfig()->get(ElevatorControlConfigKey::NUMBER_OF_FLOORS).toInt();
    
    
    context->getDeviceManager()->EMSButtonUp()->setOnClick([&](Button* button){
        Serial.print(button->getName());Serial.println(" Clicked.");
        EMSStopRequested();
    });

    context->getDeviceManager()->EMSButtonDown()->setOnClick([&](Button* button){
        Serial.print(button->getName());Serial.println(" Clicked.");
        EMSStopRequested();
    });

    context->getDeviceManager()->floorSensor1()->setOnClick([&](Button* button){
        OnFloorSensorClicked(1);
    });

    if (_elevatorMode == ElevatorMode::SEPARATE_SENSORS)
    {
        Serial.println("-------------------------------------------------");
        context->getDeviceManager()->floorSensor2()->setOnClick([&](Button* button){
            OnFloorSensorClicked(2);
        });

        context->getDeviceManager()->floorSensor3()->setOnClick([&](Button* button){
            OnFloorSensorClicked(3);
        });

        context->getDeviceManager()->floorSensor4()->setOnClick([&](Button* button){
            OnFloorSensorClicked(4);
        });

        context->getDeviceManager()->floorSensor5()->setOnClick([&](Button* button){
            OnFloorSensorClicked(5);
        });
        
    }
    else if (_elevatorMode == ElevatorMode::SINGLE_SENSOR)
    {
        context->getDeviceManager()->calibrationSensor()->setOnClick([&](Button* button){
            CalibrationSensorClicked(button);
        });

        if (context->getElevatorControlConfig()->get(ElevatorControlConfigKey::CALIBRATION_ON_STARTUP) == "true")
        {
            //if calibration sensor is no clicked, start to calibrate
            CalibrationRequested();
        }
    }
    
    for (size_t i = 0; i < numberOfFloors; i++)
    {
        context->getDeviceManager()->floorButtons(i)->setOnClick([&](Button* button){
            Serial.print(button->getName());Serial.println(" Clicked.");
            int floor = button->getName().toInt();
            FloorRequested(floor);
        });
    }

    for (size_t i = 0; i < 4; i++)
    {
        context->getDeviceManager()->floorButtonsRemote(i)->setOnClick([&](Button* button){
            Serial.print(button->getName());Serial.println(" Clicked.");
            int floor = button->getName().substring(0,1).toInt();
            FloorRequested(floor);
        });
    }
    
    // context->getDeviceManager()->SimCard()->setOnMessageReceived([&](String phoneNumber, String message){
    //     handleIncomingMessage(phoneNumber, message);
    // });
    
    
    
    context->systemContext->getLogger()->info(ElevatorLogTitles::ELEVATOR_BOOT, "Elevator Initialized Succesfully.");
    if (calibration_on_strtup)
    {
        if (_elevatorMode == ElevatorMode::SEPARATE_SENSORS)
        {
            summonFloor(parkingFloor);
            if (calibration_direction == CalibrationSensorPosition::BOTTOM)
            {
                currentFloor = 10;
            }
            else if(calibration_direction == CalibrationSensorPosition::TOP)
            {
                currentFloor = 0;
            }
        }
        else if (_elevatorMode == ElevatorMode::SINGLE_SENSOR)
        {
            CalibrationRequested();
        }
        
    }
}

String ElevatorControl::CalibrationRequested() {
    if(!isElevatorEnable)
    {
        return "بالابر غیر فعال است";
    }
    movementState = MovementState::CALIBRATING;
    context->systemContext->getLogger()->info(LogTitles::SYSTEM_BOOT, "Calibration Started.");
    context->getDeviceManager()->calibrationSensor()->update();
    if (context->getDeviceManager()->calibrationSensor()->getState())
    {
        CalibrationSensorClicked(context->getDeviceManager()->calibrationSensor());
        return "بالابر کالیبر است";
    }
    
    if (calibrationPosition == TOP) {
        context->getDeviceManager()->downRelay()->turnOff();
        context->getDeviceManager()->upRelay()->turnOnAfterDelay(relayStartDelay);
        return "حرکت به سمت بالا برای کالیبر شدن";
    } else {
        context->getDeviceManager()->upRelay()->turnOff();
        context->getDeviceManager()->downRelay()->turnOnAfterDelay(relayStartDelay);
        return "حرکت به سمت پایین برای کالیبر شدن";
    }
    return "";
}

void ElevatorControl::OnFloorSensorClicked(int floor)
{
    if (_elevatorMode == ElevatorMode::SINGLE_SENSOR)
    {
        Serial.println("1");

        if (movementState == MovementState::CALIBRATING || !isCalibrated)
        {
            Serial.println("2");
            return;
        }
            Serial.println("3");
        if(floorQueue.size()>0)
        {
            Serial.println("4 = ");
            Serial.println(floorQueue.at(0));
            if (movementState == MovementState::MOVE_DOWN)
            {
                Serial.println("5");
                currentFloor = currentFloor - 1;
                Serial.print("Moving Down - currentFloor = ");Serial.println(currentFloor);
                if (floorQueue.at(0) == currentFloor)
                {
                Serial.println("6");
                    handleCurrentFloor();
                }
                
            }
            else if (movementState == MovementState::MOVE_UP)
            {
                Serial.println("7");
                currentFloor = currentFloor + 1;
                Serial.print("Moving UP - currentFloor = ");Serial.println(currentFloor);
                if (floorQueue.at(0) == currentFloor)
                {
                Serial.println("8");
                    handleCurrentFloor();
                }
                
            }
            else if (movementState == MovementState::EMERGENCY_STOP)
            {
                Serial.println("9");
                floorQueue.clear();
                EMSStop();
            }
            else if (movementState == MovementState::STOP || movementState == MovementState::NONE || movementState == MovementState::WAITING)
            {
                //log it
                EMSStop();
            }
            
        }
        else
        {
                Serial.println("10");
            Stop(true);
        }
    }
    else
    {
                Serial.println("11");
        if(floorQueue.size()>0)
        {
            currentFloor = floor;
            if (floorQueue.at(0) == currentFloor)
            {
                handleCurrentFloor();
            }
        }
    }
    Serial.print("currentFloor = ");Serial.println(floor);
    

}

String ElevatorControl::FloorRequested(int floor)
{
    Serial.print("floor: ");Serial.println(floor);
    if(!isElevatorEnable)
    {
        return "بالابر غیر فعال است";
    }
    if (context->getDeviceManager()->EMSButtonUp()->getState())
    {
        return "کلید اضطراری فعال است";
    }
    
    if (_elevatorMode == ElevatorMode::SINGLE_SENSOR && !isCalibrated)
    {
        context->systemContext->getLogger()->error(ElevatorLogTitles::SUMMON_BEFOR_CALIBRATING, "floor requested befor calibratiion");
        CalibrationRequested();
        floorQueue.push_back(floor);
        return "بالابر کالیبر نشده است";
    }
    
    context->systemContext->getLogger()->info(ElevatorLogTitles::SUMMON_FLOOR, String("floor summoned: " + floor));
    summonFloor(floor);
    return "به سمت طبقه " + String(floor);
}


String ElevatorControl::RequestCalibration()
{
    
    return "در حال کالیبر شدن";
}

void ElevatorControl::CalibrationSensorClicked(Button* button)
{
    Serial.println("claibration sensor clicked");
    if (isCalibrationSensorWithFloorSensor && isCalibrated)
    {
        return;
    }
    
    Stop(false);
    bool move_to_parking = false;
    isCalibrated = true;
    if (movementState != MovementState::CALIBRATING && !isCalibrationSensorWithFloorSensor)
    {
        //log error
        context->systemContext->getLogger()->error(ElevatorLogTitles::CALIBRATED,"claibration sensor clicked on none Calibrating method.");
    }     
    movementState = MovementState::STOP;
    if (calibrationPosition == CalibrationSensorPosition::TOP)
    {
        if (isCalibrationSensorWithFloorSensor == 0)
        {
            currentFloor = numberOfFloors + 1;
        }
        else{
            currentFloor = numberOfFloors;
        }

        if (parkingFloor != numberOfFloors || isCalibrationSensorWithFloorSensor == 0)
        {
            move_to_parking = true;
        }
    }else{
        if (isCalibrationSensorWithFloorSensor == 0)
        {
            currentFloor = 0;
        }
        else{
            currentFloor = 1;
        }

        if (parkingFloor != 1 || isCalibrationSensorWithFloorSensor == 0)
        {
            move_to_parking = true;
        }
    }     
    Serial.print("floorQueue.size() = ");Serial.println(floorQueue.size());
    if (floorQueue.size() > 0)
    {
        Serial.print("---------       floorQueue.size() = ");Serial.println(floorQueue.size());
        Serial.print("---------       floorQueue.at(0) = ");Serial.println(floorQueue.at(0));
        int requested_floor = floorQueue.at(0);
        floorQueue.clear();
        summonFloor(requested_floor);
        return;
    }
    
    floorQueue.clear();
    if (move_to_parking)
    {
        context->systemContext->getLogger()->info(ElevatorLogTitles::CALIBRATED, "Elevator Calibrated Succesfully. Moving to Parking floor.");
        summonFloor(parkingFloor);
    }
    else{
        context->systemContext->getLogger()->info(ElevatorLogTitles::CALIBRATED, "Elevator Calibrated Succesfully. It is in Parking floor.");
        Stop(true);
    }
}

String ElevatorControl::EMSStopRequested()
{
    if (movementState == MovementState::CALIBRATING)
    {
        context->getDeviceManager()->downRelay()->turnOff();
        context->getDeviceManager()->upRelay()->turnOn();
        
    }
    
    // if (emergency_button_enabled == "true")
    // {
        EMSStop();
        // context->systemContext->getLogger()->info(ElevatorLogTitles::ELEVATOR_INFO, "EMS Button Pressed and Stoped.");
        return "توقف اضطراری";
    // }
    return "توقف اضطراری فعال نیست";
}


void ElevatorControl::MoveUp()
{
    context->systemContext->getLogger()->info(ElevatorLogTitles::ELEVATOR_INFO, "Moving Up");
    movementState = MovementState::MOVE_UP;
    context->getDeviceManager()->downRelay()->turnOff();
    context->getDeviceManager()->upRelay()->turnOnAfterDelay(relayStartDelay);
}


void ElevatorControl::MoveDown()
{
    context->systemContext->getLogger()->info(ElevatorLogTitles::ELEVATOR_INFO, "Moving Down");
    movementState = MovementState::MOVE_DOWN;
    context->getDeviceManager()->upRelay()->turnOff();
    context->getDeviceManager()->downRelay()->turnOnAfterDelay(relayStartDelay);
}

void ElevatorControl::Stop(bool changeState)
{
    context->systemContext->getLogger()->info(ElevatorLogTitles::ELEVATOR_INFO, "Stopped");
    if (changeState)
    {
        movementState = MovementState::STOP;
    }
    
    context->getDeviceManager()->upRelay()->turnOffAfterDelay(floor_sensor_interval);
    context->getDeviceManager()->downRelay()->turnOffAfterDelay(floor_sensor_interval);
}

void ElevatorControl::EMSStop()
{
    // context->systemContext->getLogger()->info(ElevatorLogTitles::ELEVATOR_INFO, "Emergensy Button pressed");
    movementState = MovementState::EMERGENCY_STOP;
    context->getDeviceManager()->upRelay()->turnOff();
    context->getDeviceManager()->downRelay()->turnOff();
    // context->systemContext->getLogger()->error("EMS", "Elevator Stopped by pressing EMS");
}

void ElevatorControl::summonFloor(int floor) {
    Serial.print("floor = ");
    Serial.println(floor);
    Serial.print("numberOfFloors = ");
    Serial.println(numberOfFloors);

    if (floor <= numberOfFloors && floor >= 0)
    {
        floorQueue.push_back(floor);
    }
    //added this code to not summon all floors. this code is using for an simple elevator board
    Serial.print("floorQueue.size() = ");Serial.println(floorQueue.size());
    if (floorQueue.size() > 1)
    {
        floorQueue.erase(floorQueue.begin());
    }
    moveToNextFloor();   
}

void ElevatorControl::moveToNextFloor() {
    if (!floorQueue.empty()) {
        if (floorQueue.at(0) > currentFloor)
        {
            MoveUp();
        }
        else if (floorQueue.at(0) < currentFloor)
        {
            MoveDown();
        }        
    }
}

void ElevatorControl::handleCurrentFloor() {
    if (!floorQueue.empty()) {
        Stop(true);
        floorQueue.erase(floorQueue.begin());
    }
}

MovementState ElevatorControl::getState()
{
    return movementState;
}

void ElevatorControl::setMovementMethod(MovementMethod movementMethod)
{
    _movementMethod = movementMethod;    
}

MovementMethod ElevatorControl::getMovementMethod()
{
    return _movementMethod;
}

void ElevatorControl::MoveUpManual()
{
    if (_movementMethod == MovementMethod::MANUAL)
    {
        context->getDeviceManager()->downRelay()->turnOff();
        context->getDeviceManager()->upRelay()->turnOnAfterDelay(relayStartDelay);
    }    
}

void ElevatorControl::MoveDownManual()
{
    if (_movementMethod == MovementMethod::MANUAL)
    {
        context->getDeviceManager()->upRelay()->turnOff();
        context->getDeviceManager()->downRelay()->turnOnAfterDelay(relayStartDelay);
    }
}

void ElevatorControl::StopManual()
{
    if (_movementMethod == MovementMethod::MANUAL)
    {
        context->getDeviceManager()->upRelay()->turnOff();
        context->getDeviceManager()->downRelay()->turnOff();
    }
}


void ElevatorControl::update() {
    // context->getDeviceManager()->mainLCD()->Clean();
    // context->getDeviceManager()->mainLCD()->drawText(getLCDMessage(),1);

    display->displayNumber(currentFloor);


}

int ElevatorControl::GetCurrentFLoor()
{
    return currentFloor;
}

String ElevatorControl::getLCDMessagePersian()
{
    if(!isElevatorEnable)
    {
        return "بالابر غیر فعال است";
    }
    else if (movementState == MovementState::EMERGENCY_STOP)
    {
        return "توقف اضطراری";
    }
    else if (movementState == MovementState::MOVE_DOWN)
    {
        return "حرکت به سمت پایین - " + currentFloor;
    }
    else if (movementState == MovementState::MOVE_UP)
    {
        return "حرکت به سمت بالا - " + currentFloor;
    }
    else if (movementState == MovementState::STOP)
    {
        return String(currentFloor);
    }
    return "";
}

String ElevatorControl::getLCDMessage()
{
    if(!isElevatorEnable)
    {
        return "Elevator is Disable";
    }
    else if (movementState == MovementState::EMERGENCY_STOP)
    {
        return "Emergency Stop";
    }
    else if (movementState == MovementState::MOVE_DOWN)
    {
        return "Moving Down";
    }
    else if (movementState == MovementState::MOVE_UP)
    {
        return "Moving Up";
    }
    else if (movementState == MovementState::STOP)
    {
        return String(currentFloor);
    }
    return "";
}

void ElevatorControl::handleIncomingMessage(String phoneNumber, String message)
{
    String adminphoneNumber = "+" + context->getElevatorControlConfig()->get(ElevatorControlConfigKey::ADMIN_PHONE_NUMBER);
    if (adminphoneNumber == "")
    {
        context->systemContext->getLogger()->info(LogTitles::SIM800_MESSAGE_RECIEVED, "message recieved but admin phone number is null");
        return;
    }
    if (adminphoneNumber != phoneNumber)
    {
        context->systemContext->getLogger()->info(LogTitles::SIM800_MESSAGE_RECIEVED, "message recieved but is not same with admin phone number");
        return;
    }
    if (adminphoneNumber == phoneNumber)
    {
        context->systemContext->getLogger()->info(LogTitles::SIM800_MESSAGE_RECIEVED, message);
        if (isInt(message))
        {
            if(!isElevatorEnable)
            {
                return;
            }

            if (message.toInt() > 0 && message.toInt() <= numberOfFloors)
            {
                FloorRequested(message.toInt());
            }
        }
    }
}

bool ElevatorControl::isInt(String str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isDigit(str[i])) {
            return false;
        }
    }
    return true;
}

void ElevatorControl::setElevatorMode(ElevatorMode elevatorMode)
{
    _elevatorMode = elevatorMode;
}

ElevatorMode ElevatorControl::getElevatorMode()
{
    return _elevatorMode;
}

#endif //ELEVATORCONTROL_H
