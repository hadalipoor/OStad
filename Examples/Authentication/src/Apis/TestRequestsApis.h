
#ifndef TestRequestsApis_h
#define TestRequestsApis_h


#include "../AppContext.h"
#include "Permissions.h"
class TestRequestsApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/testrequests";

public:
    TestRequestsApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleaddData(String data);
    String handlegetData();
    String handlepublicRequest();
};

TestRequestsApis::TestRequestsApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/addData"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TESTREQUESTS_ADDDATA) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("data")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String data = getQueryParameterString(req, "data");
        
        response(res, handleaddData(data));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getData"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TESTREQUESTS_GETDATA) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlegetData());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/publicRequest"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TESTREQUESTS_PUBLICREQUEST) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handlepublicRequest());
    }));
}

String TestRequestsApis::getClassPath()
{
    return String(class_path.c_str());
}



String TestRequestsApis::handleaddData(String data) {
    return "";
}
String TestRequestsApis::handlegetData() {
    return "";
}
String TestRequestsApis::handlepublicRequest() {
    return "";
}

String TestRequestsApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleaddData") {
        handleaddData(parameters["data"]);
        return "OK";
    }
    if (functionName == "handlegetData") {
        handlegetData();
        return "OK";
    }
    if (functionName == "handlepublicRequest") {
        handlepublicRequest();
        return "OK";
    }
    return "";
}

#endif //TestRequestsApis_h
