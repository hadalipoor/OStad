
#ifndef ElevatorControlApis_h
#define ElevatorControlApis_h


#include "../AppContext.h"
#include "../Config/ElevatorControlConfigKeys.h"

class ElevatorControlApis : public ApiInterface
{
private:
    AppContext* context;
    String class_path = "/elevatorcontrol";

public:
    ElevatorControlApis(AppContext* cntxt);
    void initialize(AsyncWebServer &server) override;
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlemoveUpManual();
    String handlemoveDownManual();
    String handlestopManual();
    String handlefloorRequested(String floor);
    String handlecalibrationRequested();
    String handleeMSStopRequested();
    String handlesetMovementMethod(String method);
    String handlegetMovementMethod();
    String handlegetState();
};

ElevatorControlApis::ElevatorControlApis(AppContext* cntxt): context(cntxt) {
    
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/moveUpManual").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_MOVEUPMANUAL)){return;}
        
        
        request->send(200, "text/html", handlemoveUpManual());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/moveDownManual").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_MOVEDOWNMANUAL)){return;}
        
        
        request->send(200, "text/html", handlemoveDownManual());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/stopManual").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_STOPMANUAL)){return;}
        
        
        request->send(200, "text/html", handlestopManual());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/floorRequested").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_FLOORREQUESTED)){return;}
        
        String floor = request->getParam("floor")->value();
        
        request->send(200, "text/html", handlefloorRequested(floor));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/calibrationRequested").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_CALIBRATIONREQUESTED)){return;}
        
        
        request->send(200, "text/html", handlecalibrationRequested());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/eMSStopRequested").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_EMSSTOPREQUESTED)){return;}
        
        
        request->send(200, "text/html", handleeMSStopRequested());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/setMovementMethod").c_str(), HTTP_POST, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_SETMOVEMENTMETHOD)){return;}
        
        String method = request->getParam("method")->value();
        
        request->send(200, "text/html", handlesetMovementMethod(method));
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getMovementMethod").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_GETMOVEMENTMETHOD)){return;}
        
        
        request->send(200, "text/html", handlegetMovementMethod());
    });
    context->systemContext->getNetwork()->getServer().on(String(class_path + "/getState").c_str(), HTTP_GET, [=](AsyncWebServerRequest * request) {
        // if (!context->systemContext->getSecurity()->checkAuthentication(request, Permissions::ELEVATORCONTROL_GETSTATE)){return;}
        
        
        request->send(200, "text/html", handlegetState());
    });
}

void ElevatorControlApis::initialize(AsyncWebServer &server)
{

}

String ElevatorControlApis::getClassPath()
{
    return String(class_path.c_str());
}



String ElevatorControlApis::handlemoveUpManual() {
    context->getDeviceManager()->upRelay()->turnOnForDelay(context->getElevatorControlConfig()->get(ElevatorControlConfigKey::MANUAL_MOVE_UP_MILIS).toInt());
    return "حرکت به سمت بالا";
}
String ElevatorControlApis::handlemoveDownManual() {
    context->getDeviceManager()->downRelay()->turnOnForDelay(context->getElevatorControlConfig()->get(ElevatorControlConfigKey::MANUAL_MOVE_UP_MILIS).toInt());
    return "حرکت به سمت پایین";
}
String ElevatorControlApis::handlestopManual() {
    context->getDeviceManager()->upRelay()->turnOff();
    context->getDeviceManager()->downRelay()->turnOff();
    return "متوقف";
}
String ElevatorControlApis::handlefloorRequested(String floor) {
    return context->getElevatorControl()->FloorRequested(floor.toInt());
}
String ElevatorControlApis::handlecalibrationRequested() {
    return context->getElevatorControl()->RequestCalibration();
}
String ElevatorControlApis::handleeMSStopRequested() {
    return context->getElevatorControl()->EMSStopRequested();
}
String ElevatorControlApis::handlesetMovementMethod(String method) {
    if (method == "manual")
    {
        context->getElevatorControl()->setMovementMethod(MovementMethod::MANUAL);
    }
    else if (method == "automatic")
    {
        context->getElevatorControl()->setMovementMethod(MovementMethod::AUTOMATIC);
    }
    return "Successfull";
}
String ElevatorControlApis::handlegetMovementMethod() {
    MovementMethod movementmethod = context->getElevatorControl()->getMovementMethod();
    if (movementmethod == MovementMethod::AUTOMATIC)
    {
        return "automatic";
    }
    else if (movementmethod == MovementMethod::MANUAL)
    {
        return "manual";
    }
}
String ElevatorControlApis::handlegetState() {
    MovementState movementstate = context->getElevatorControl()->getState();
    if (movementstate == MovementState::CALIBRATING)
    {
        return "در حال کالیبر شدن";
    }
    else if (movementstate == MovementState::EMERGENCY_STOP)
    {
        return "توقف اضطراری";
    }
    else if (movementstate == MovementState::MOVE_DOWN)
    {
        return "به سمت پایین";
    }
    else if (movementstate == MovementState::MOVE_UP)
    {
        return "به سمت بالا";
    }
    else if (movementstate == MovementState::STOP)
    {
        return "توقف";
    }
    else if (movementstate == MovementState::WAITING)
    {
        return "در حال انتظار";
    }
}


String ElevatorControlApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlemoveUpManual") {
        handlemoveUpManual();
        return "OK";
    }
    if (functionName == "handlemoveDownManual") {
        handlemoveDownManual();
        return "OK";
    }
    if (functionName == "handlestopManual") {
        handlestopManual();
        return "OK";
    }
    if (functionName == "handlefloorRequested") {
        handlefloorRequested(parameters["floor"]);
        return "OK";
    }
    if (functionName == "handlecalibrationRequested") {
        handlecalibrationRequested();
        return "OK";
    }
    if (functionName == "handleeMSStopRequested") {
        handleeMSStopRequested();
        return "OK";
    }
    if (functionName == "handlesetMovementMethod") {
        handlesetMovementMethod(parameters["method"]);
        return "OK";
    }
    if (functionName == "handlegetMovementMethod") {
        handlegetMovementMethod();
        return "OK";
    }
    if (functionName == "handlegetState") {
        handlegetState();
        return "OK";
    }
    return "";
}

#endif //ElevatorControlApis_h
