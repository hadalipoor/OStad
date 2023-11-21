
#ifndef GreenhousesApis_h
#define GreenhousesApis_h


#include "../AppContext.h"
#include "Permissions.h"
class GreenhousesApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/greenhouses";

public:
    GreenhousesApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleswitchModule(String module_id, String status);
    String handlesetCondition(String greenhouse_id, String condition_id);
};

GreenhousesApis::GreenhousesApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/switchModule"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSES_SWITCHMODULE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("module_id") || !req->getParams()->isQueryParameterSet("status")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String module_id = getQueryParameterString(req, "module_id");
        String status = getQueryParameterString(req, "status");
        
        response(res, handleswitchModule(module_id, status));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/setCondition"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::GREENHOUSES_SETCONDITION) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("greenhouse_id") || !req->getParams()->isQueryParameterSet("condition_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String greenhouse_id = getQueryParameterString(req, "greenhouse_id");
        String condition_id = getQueryParameterString(req, "condition_id");
        
        response(res, handlesetCondition(greenhouse_id, condition_id));
    }));
}

String GreenhousesApis::getClassPath()
{
    return String(class_path.c_str());
}



String GreenhousesApis::handleswitchModule(String module_id, String status) {
    return "";
}
String GreenhousesApis::handlesetCondition(String greenhouse_id, String condition_id) {
    return "";
}

String GreenhousesApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleswitchModule") {
        handleswitchModule(parameters["module_id"], parameters["status"]);
        return "OK";
    }
    if (functionName == "handlesetCondition") {
        handlesetCondition(parameters["greenhouse_id"], parameters["condition_id"]);
        return "OK";
    }
    return "";
}

#endif //GreenhousesApis_h
