
#ifndef ConditionsApis_h
#define ConditionsApis_h


#include "../AppContext.h"
#include "Permissions.h"
class ConditionsApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/conditions";

public:
    ConditionsApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlegetCurrentConditions(String greenhouse_id);
};

ConditionsApis::ConditionsApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getCurrentConditions"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::CONDITIONS_GETCURRENTCONDITIONS) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("greenhouse_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String greenhouse_id = getQueryParameterString(req, "greenhouse_id");
        
        response(res, handlegetCurrentConditions(greenhouse_id));
    }));
}

String ConditionsApis::getClassPath()
{
    return String(class_path.c_str());
}



String ConditionsApis::handlegetCurrentConditions(String greenhouse_id) {
    return "";
}

String ConditionsApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlegetCurrentConditions") {
        handlegetCurrentConditions(parameters["greenhouse_id"]);
        return "OK";
    }
    return "";
}

#endif //ConditionsApis_h
