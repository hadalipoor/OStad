#ifndef REQUESTLOGAPIS_h
#define REQUESTLOGAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/RequestLogController.h"
#include "Permissions.h"

class RequestLogApis : public ApiInterface
{
private:
    AppContext* context;
    RequestLogController* requestlogController;
    std::string class_path = "/requestlog";

public:
    RequestLogApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int RequestFloor, String Direction, String RequestTime);
    String handleupdate(int id, int RequestFloor, String Direction, String RequestTime);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

RequestLogApis::RequestLogApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    requestlogController = new RequestLogController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::REQUESTLOG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("RequestFloor") || !req->getParams()->isQueryParameterSet("Direction") || !req->getParams()->isQueryParameterSet("RequestTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int RequestFloor = getQueryParameterint(req, "RequestFloor");
    String Direction = getQueryParameterString(req, "Direction");
    String RequestTime = getQueryParameterString(req, "RequestTime");

        response(res, handlecreate(RequestFloor, Direction, RequestTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::REQUESTLOG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("RequestFloor") || !req->getParams()->isQueryParameterSet("Direction") || !req->getParams()->isQueryParameterSet("RequestTime"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int RequestFloor = getQueryParameterint(req, "RequestFloor");
    String Direction = getQueryParameterString(req, "Direction");
    String RequestTime = getQueryParameterString(req, "RequestTime");
        
        response(res, handleupdate(id, RequestFloor, Direction, RequestTime));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::REQUESTLOG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::REQUESTLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::REQUESTLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::REQUESTLOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String RequestLogApis::getClassPath()
{
    return String(class_path.c_str());
}

String RequestLogApis::handlecreate(int RequestFloor, String Direction, String RequestTime) {
    RequestLogEntity* requestlogEntity = new RequestLogEntity(RequestFloor, Direction, RequestTime);
    int id = requestlogController->Add(*requestlogEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String RequestLogApis::handleupdate(int id, int RequestFloor, String Direction, String RequestTime) {
    RequestLogEntity* requestlogEntity = new RequestLogEntity(id, RequestFloor, Direction, RequestTime);
    
    if (requestlogController->Update(*requestlogEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String RequestLogApis::handledelete(int id) {
    
    if (requestlogController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String RequestLogApis::handlegetAll() {
    return requestlogController->GetAllJson();
}
String RequestLogApis::handlegetById(int id) {
    return requestlogController->GetById(id).toJson();
}
String RequestLogApis::handleget(String query) {
    return requestlogController->GetJson(query);
}

String RequestLogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["RequestFloor"].toInt(), parameters["Direction"], parameters["RequestTime"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["RequestFloor"].toInt(), parameters["Direction"], parameters["RequestTime"]);
    }
    if (functionName == "delete") {
        return handledelete(parameters["id"].toInt());
    }
    if (functionName == "getAll") {
        return handlegetAll();
    }
    if (functionName == "getById") {
        return handlegetById(parameters["id"].toInt());
    }
    if (functionName == "get") {
        return handleget(parameters["query"]);
    }
    return String(NO_FUNCTION_MESSAGE + functionName);
}

#endif //REQUESTLOGApis_h

    