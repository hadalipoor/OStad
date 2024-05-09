
#ifndef RelayControllerApis_h
#define RelayControllerApis_h


#include "../../../Context.h"
#include "ModulePermissions.h"
#include "../../../Database/Controllers/Modules/ModulesController.h"
#include "../../../ModuleManager/Modules/Relay.h"
class RelayControllerApis : public ApiInterface
{
private:
    Context* context;
    std::string class_path = "/relaycontroller";
    ModulesController* modulecontroller;

public:
    RelayControllerApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleturn_on(String serverid);
    String handleturn_on_after_delay(String delay_millis, String serverid);
    String handleturn_off(String serverid);
    String handleturn_off_after_delay(String delay_millis, String serverid);
    String handleturn_on_for_delay(String delay_millis, String serverid);
    String handleturn_off_for_delay(String delay_millis, String serverid);
    String handleget_state(String serverid);
    String handleset_normally_open(String normallyopen, String serverid);
    String handleget_normally_open(String serverid);
    String handleset_pin_number(String pinnumber, String serverid);
    String handleget_pin_number(String serverid);
    String handleget_entity(String serverid);
};

RelayControllerApis::RelayControllerApis(Context* cntxt, bool add_apis): context(cntxt) {
    modulecontroller = new ModulesController(context, storageType);
    if (!add_apis) return;

    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_on"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_TURN_ON) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleturn_on(serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_on_after_delay"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_TURN_ON_AFTER_DELAY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("delay_millis") || !req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String delay_millis = getQueryParameterString(req, "delay_millis");
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleturn_on_after_delay(delay_millis, serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_off"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_TURN_OFF) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleturn_off(serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_off_after_delay"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_TURN_OFF_AFTER_DELAY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("delay_millis") || !req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String delay_millis = getQueryParameterString(req, "delay_millis");
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleturn_off_after_delay(delay_millis, serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_on_for_delay"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_TURN_ON_FOR_DELAY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("delay_millis") || !req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String delay_millis = getQueryParameterString(req, "delay_millis");
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleturn_on_for_delay(delay_millis, serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/turn_off_for_delay"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_TURN_OFF_FOR_DELAY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("delay_millis") || !req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String delay_millis = getQueryParameterString(req, "delay_millis");
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleturn_off_for_delay(delay_millis, serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_state"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_GET_STATE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleget_state(serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/set_normally_open"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_SET_NORMALLY_OPEN) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("normally_open") || !req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String normallyopen = getQueryParameterString(req, "normally_open");
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleset_normally_open(normallyopen, serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_normally_open"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_GET_NORMALLY_OPEN) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleget_normally_open(serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/set_pin_number"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_SET_PIN_NUMBER) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("pin_number") || !req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String pinnumber = getQueryParameterString(req, "pin_number");
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleset_pin_number(pinnumber, serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_pin_number"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_GET_PIN_NUMBER) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleget_pin_number(serverid));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_entity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, ModulePermissions::RELAYMANAGER_GET_ENTITY) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("server_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String serverid = getQueryParameterString(req, "server_id");
        
        response(res, handleget_entity(serverid));
    }));
}

String RelayControllerApis::getClassPath()
{
    return String(class_path.c_str());
}



String RelayControllerApis::handleturn_on(String serverid) {
    context->getModules()->getRelay(serverid.toInt())->turnOn();
    return "Successful";
}
String RelayControllerApis::handleturn_on_after_delay(String delay_millis, String serverid) {
    context->getModules()->getRelay(serverid.toInt())->turnOnAfterDelay(delay_millis.toInt());
    return "Successful";
}
String RelayControllerApis::handleturn_off(String serverid) {
    IRelay* _relay = context->getModules()->getRelay(serverid.toInt());
    _relay->turnOff();
    return "Successful";
}
String RelayControllerApis::handleturn_off_after_delay(String delay_millis, String serverid) {
    context->getModules()->getRelay(serverid.toInt())->turnOffAfterDelay(delay_millis.toInt());
    return "Successful";
}
String RelayControllerApis::handleturn_on_for_delay(String delay_millis, String serverid) {
    context->getModules()->getRelay(serverid.toInt())->turnOnForDelay(delay_millis.toInt());
    return "Successful";
}
String RelayControllerApis::handleturn_off_for_delay(String delay_millis, String serverid) {
    context->getModules()->getRelay(serverid.toInt())->turnOffForDelay(delay_millis.toInt());
    return "Successful";
}
String RelayControllerApis::handleget_state(String serverid) {
    return String(context->getModules()->getRelay(serverid.toInt())->getState());
}
String RelayControllerApis::handleset_normally_open(String normallyopen, String serverid) {
    context->getModules()->getRelay(serverid.toInt())->setNormallyOpen(normallyopen.toInt());
    return "Successful";
}
String RelayControllerApis::handleget_normally_open(String serverid) {
    return context->getModules()->getRelay(serverid.toInt())->getNormallyOpen() ? "true" : "false";
}
String RelayControllerApis::handleset_pin_number(String pinnumber, String serverid) {
    context->getModules()->getRelay(serverid.toInt())->setNormallyOpen(pinnumber.toInt());
    return "Successful";
}
String RelayControllerApis::handleget_pin_number(String serverid) {
    return String(context->getModules()->getRelay(serverid.toInt())->getPinNumber());
}
String RelayControllerApis::handleget_entity(String serverid) {
    RelayFullEntity* relay = context->getModules()->getRelay(serverid.toInt())->getEntity();

    return relay->getJsonString();
}

String RelayControllerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleturn_on") {
        handleturn_on(parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleturn_on_after_delay") {
        handleturn_on_after_delay(parameters["delay_millis"], parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleturn_off") {
        handleturn_off(parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleturn_off_after_delay") {
        handleturn_off_after_delay(parameters["delay_millis"], parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleturn_on_for_delay") {
        handleturn_on_for_delay(parameters["delay_millis"], parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleturn_off_for_delay") {
        handleturn_off_for_delay(parameters["delay_millis"], parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleget_state") {
        handleget_state(parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleset_normally_open") {
        handleset_normally_open(parameters["normallyopen"], parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleget_normally_open") {
        handleget_normally_open(parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleset_pin_number") {
        handleset_pin_number(parameters["pinnumber"], parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleget_pin_number") {
        handleget_pin_number(parameters["server_id"]);
        return "OK";
    }
    if (functionName == "handleget_entity") {
        handleget_entity(parameters["server_id"]);
        return "OK";
    }
    return "";
}

#endif //RelayControllerApis_h
