
#ifndef TagControllerApis_h
#define TagControllerApis_h


#include "../AppContext.h"
#include "Permissions.h"
class TagControllerApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/tagcontroller";

public:
    TagControllerApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleaddGuest(String name, String description, String start_active_time, String end_active_time);
    String handleopenDoor();
};

TagControllerApis::TagControllerApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/addGuest"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TAGCONTROLLER_ADDGUEST) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("description") || !req->getParams()->isQueryParameterSet("start_active_time") || !req->getParams()->isQueryParameterSet("end_active_time")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String name = getQueryParameterString(req, "name");
        String description = getQueryParameterString(req, "description");
        String start_active_time = getQueryParameterString(req, "start_active_time");
        String end_active_time = getQueryParameterString(req, "end_active_time");
        
        response(res, handleaddGuest(name, description, start_active_time, end_active_time));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/openDoor"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TAGCONTROLLER_OPENDOOR) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handleopenDoor());
    }));
}

String TagControllerApis::getClassPath()
{
    return String(class_path.c_str());
}



String TagControllerApis::handleaddGuest(String name, String description, String start_active_time, String end_active_time) {
    return "";
}
String TagControllerApis::handleopenDoor() {
    return "";
}

String TagControllerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleaddGuest") {
        handleaddGuest(parameters["name"], parameters["description"], parameters["start_active_time"], parameters["end_active_time"]);
        return "OK";
    }
    if (functionName == "handleopenDoor") {
        handleopenDoor();
        return "OK";
    }
    return "";
}

#endif //TagControllerApis_h
