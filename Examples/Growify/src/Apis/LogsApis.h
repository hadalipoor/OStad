
#ifndef LogsApis_h
#define LogsApis_h


#include "../AppContext.h"
#include "Permissions.h"
class LogsApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/logs";

public:
    LogsApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlegetLogsByDateRange(String start_date, String end_date);
};

LogsApis::LogsApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getLogsByDateRange"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LOGS_GETLOGSBYDATERANGE) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("start_date") || !req->getParams()->isQueryParameterSet("end_date")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String start_date = getQueryParameterString(req, "start_date");
        String end_date = getQueryParameterString(req, "end_date");
        
        response(res, handlegetLogsByDateRange(start_date, end_date));
    }));
}

String LogsApis::getClassPath()
{
    return String(class_path.c_str());
}



String LogsApis::handlegetLogsByDateRange(String start_date, String end_date) {
    return "";
}

String LogsApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlegetLogsByDateRange") {
        handlegetLogsByDateRange(parameters["start_date"], parameters["end_date"]);
        return "OK";
    }
    return "";
}

#endif //LogsApis_h
