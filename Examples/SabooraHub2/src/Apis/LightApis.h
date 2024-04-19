
#ifndef LightApis_h
#define LightApis_h


#include "../AppContext.h"
#include "Permissions.h"

class LightApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/light";

public:
    LightApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleswitch_garden_lights(String status);
    String handleswitch_gazebo_lights(String status);
    String handleopenDoor();
};

LightApis::LightApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/switch_garden_lights"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHT_SWITCH_GARDEN_LIGHTS) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("status")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String status = getQueryParameterString(req, "status");
        
        response(res, handleswitch_garden_lights(status));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/switch_gazebo_lights"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHT_SWITCH_GAZEBO_LIGHTS) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("status")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String status = getQueryParameterString(req, "status");
        
        response(res, handleswitch_gazebo_lights(status));
    }));
}

String LightApis::getClassPath()
{
    return String(class_path.c_str());
}



String LightApis::handleswitch_garden_lights(String status) {
    if (status == "on")
    {
        context->getDeviceManager()->gazebo1lightRelay()->turnOn();
        context->getDeviceManager()->gazebo2lightRelay()->turnOn();
        return "Turned On";
    }
    else{
        context->getDeviceManager()->gazebo1lightRelay()->turnOff();
        context->getDeviceManager()->gazebo2lightRelay()->turnOff();
        return "Turned Off";
    }
}

String LightApis::handleswitch_gazebo_lights(String status) {
    if (status == "on")
    {
        context->getDeviceManager()->gardenRelay()->turnOn();
        return "Turned On";
    }
    else{
        context->getDeviceManager()->gardenRelay()->turnOff();
        return "Turned Off";
    }
}

String LightApis::handleopenDoor()
{
    context->getSabooraHub2()->OpenTheDoor();
    return "Successful";
}

String LightApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleswitch_garden_lights") {
        handleswitch_garden_lights(parameters["status"]);
        return "OK";
    }
    if (functionName == "handleswitch_gazebo_lights") {
        handleswitch_gazebo_lights(parameters["status"]);
        return "OK";
    }
    return "";
}

#endif //LightApis_h
