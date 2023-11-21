
#ifndef PlantsApis_h
#define PlantsApis_h


#include "../AppContext.h"
#include "Permissions.h"
class PlantsApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/plants";

public:
    PlantsApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlesetPlantCondition(String plant_id, String condition_id);
    String handlegetPlantLog(String plant_id);
};

PlantsApis::PlantsApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/setPlantCondition"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTS_SETPLANTCONDITION) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("plant_id") || !req->getParams()->isQueryParameterSet("condition_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String plant_id = getQueryParameterString(req, "plant_id");
        String condition_id = getQueryParameterString(req, "condition_id");
        
        response(res, handlesetPlantCondition(plant_id, condition_id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getPlantLog"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTS_GETPLANTLOG) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("plant_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String plant_id = getQueryParameterString(req, "plant_id");
        
        response(res, handlegetPlantLog(plant_id));
    }));
}

String PlantsApis::getClassPath()
{
    return String(class_path.c_str());
}



String PlantsApis::handlesetPlantCondition(String plant_id, String condition_id) {
    return "";
}
String PlantsApis::handlegetPlantLog(String plant_id) {
    return "";
}

String PlantsApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlesetPlantCondition") {
        handlesetPlantCondition(parameters["plant_id"], parameters["condition_id"]);
        return "OK";
    }
    if (functionName == "handlegetPlantLog") {
        handlegetPlantLog(parameters["plant_id"]);
        return "OK";
    }
    return "";
}

#endif //PlantsApis_h
