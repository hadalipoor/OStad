
#ifndef TankerApis_h
#define TankerApis_h


#include "../AppContext.h"
#include "Permissions.h"
class TankerApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/tanker";

public:
    TankerApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handleget_capacity();
};

TankerApis::TankerApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get_capacity"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TANKER_GET_CAPACITY) == AuthorizationResults::SUCCESFULL){return;}
        
        response(res, handleget_capacity());
    }));
}

String TankerApis::getClassPath()
{
    return String(class_path.c_str());
}

String TankerApis::handleget_capacity() {
    return String(context->getDeviceManager()->getCapacity());
}

String TankerApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handleget_capacity") {
        handleget_capacity();
        return "OK";
    }
    return "";
}

#endif //TankerApis_h
