#ifndef LOGAPIS_h
#define LOGAPIS_h

#include "../../../Context.h"
#include "../../../Database/Controllers/LogController.h"
#include "SystemPermissions.h"

class LogApis : public ApiInterface
{
private:
    Context* context;
    LogController* logController;
    std::string class_path = "/log";

public:
    LogApis(Context* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String logLevel, String logTitle, String message);
    String handleupdate(int id, String logLevel, String logTitle, String message);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

LogApis::LogApis(Context* cntxt, bool add_apis): context(cntxt) {
    logController = new LogController(context, storageType);

    if (!add_apis) return;    

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::LOG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("logLevel") || !req->getParams()->isQueryParameterSet("logTitle") || !req->getParams()->isQueryParameterSet("message"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String logLevel = getQueryParameterString(req, "logLevel");
    String logTitle = getQueryParameterString(req, "logTitle");
    String message = getQueryParameterString(req, "message");

        response(res, handlecreate(logLevel, logTitle, message));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::LOG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("logLevel") || !req->getParams()->isQueryParameterSet("logTitle") || !req->getParams()->isQueryParameterSet("message"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String logLevel = getQueryParameterString(req, "logLevel");
    String logTitle = getQueryParameterString(req, "logTitle");
    String message = getQueryParameterString(req, "message");
        
        response(res, handleupdate(id, logLevel, logTitle, message));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::LOG_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::LOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::LOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::LOG_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String LogApis::getClassPath()
{
    return String(class_path.c_str());
}

String LogApis::handlecreate(String logLevel, String logTitle, String message) {
    LogEntity* logEntity = new LogEntity(logLevel, logTitle, message);
    int id = logController->Add(*logEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String LogApis::handleupdate(int id, String logLevel, String logTitle, String message) {
    LogEntity* logEntity = new LogEntity(id, logLevel, logTitle, message);
    
    if (logController->Update(*logEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String LogApis::handledelete(int id) {
    
    if (logController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String LogApis::handlegetAll() {
    return logController->GetAllJson();
}
String LogApis::handlegetById(int id) {
    return logController->GetById(id).toJson();
}
String LogApis::handleget(String query) {
    return logController->GetJson(query);
}

String LogApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["logLevel"], parameters["logTitle"], parameters["message"]);
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["logLevel"], parameters["logTitle"], parameters["message"]);
    }
    if (functionName == "handledelete") {
        return handledelete(parameters["id"].toInt());
    }
    if (functionName == "handlegetAll") {
        return handlegetAll();
    }
    if (functionName == "handlegetById") {
        return handlegetById(parameters["id"].toInt());
    }
    if (functionName == "handleget") {
        return handleget(parameters["query"]);
    }
    return String(NO_FUNCTION_MESSAGE + functionName);
}

#endif //LOGApis_h

    