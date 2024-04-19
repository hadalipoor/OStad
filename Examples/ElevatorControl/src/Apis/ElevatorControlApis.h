
#ifndef ElevatorControlApis_h
#define ElevatorControlApis_h


#include "../AppContext.h"
#include "Permissions.h"
class ElevatorControlApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/elevatorcontrol";

public:
    ElevatorControlApis(AppContext* cntxt, bool add_apis);
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

ElevatorControlApis::ElevatorControlApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/moveUpManual"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_MOVEUPMANUAL) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlemoveUpManual());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/moveDownManual"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_MOVEDOWNMANUAL) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlemoveDownManual());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/stopManual"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_STOPMANUAL) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlestopManual());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/floorRequested"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_FLOORREQUESTED) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("floor")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String floor = getQueryParameterString(req, "floor");
        
        response(res, handlefloorRequested(floor));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/calibrationRequested"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_CALIBRATIONREQUESTED) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlecalibrationRequested());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/eMSStopRequested"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_EMSSTOPREQUESTED) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handleeMSStopRequested());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/setMovementMethod"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_SETMOVEMENTMETHOD) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("method")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String method = getQueryParameterString(req, "method");
        
        response(res, handlesetMovementMethod(method));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getMovementMethod"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_GETMOVEMENTMETHOD) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetMovementMethod());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getState"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::ELEVATORCONTROL_GETSTATE) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetState());
    }));
}

String ElevatorControlApis::getClassPath()
{
    return String(class_path.c_str());
}



String ElevatorControlApis::handlemoveUpManual() {
    return "";
}
String ElevatorControlApis::handlemoveDownManual() {
    return "";
}
String ElevatorControlApis::handlestopManual() {
    return "";
}
String ElevatorControlApis::handlefloorRequested(String floor) {
    return "";
}
String ElevatorControlApis::handlecalibrationRequested() {
    return "";
}
String ElevatorControlApis::handleeMSStopRequested() {
    return "";
}
String ElevatorControlApis::handlesetMovementMethod(String method) {
    return "";
}
String ElevatorControlApis::handlegetMovementMethod() {
    return "";
}
String ElevatorControlApis::handlegetState() {
    return "";
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
