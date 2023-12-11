
#ifndef AUTHORIZATIONCONFIGAPIS_h
#define AUTHORIZATIONCONFIGAPIS_h


#include <ArduinoJson.h>
#include "../../../Database/Controllers/Security/AuthenticationConfigController.h"
#include "../../../Context.h"
#include "../ApiInterface.h"
#include "../../../Config/Security/DefaultSecurityConfigs.h"

class AuthenticatioConfigApis : public ApiInterface
{
private:
public:
    std::string class_path = "/authenticationConfig";
    AuthenticationConfigController* authenticationConfigController;
    Context* context;

    AuthenticatioConfigApis(Context* context, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    String handleCreate(String key, String value);
    String handleUpdate(int id, String key, String value);
    String handleSubmit(String key, String value);
    String handleDelete(int id);
    String handleGet(String query);
    String handleGetById(int id);
    String handleGetAll();
};

AuthenticatioConfigApis::AuthenticatioConfigApis(Context* cntxt, bool add_apis): context(cntxt)
{
    authenticationConfigController = new AuthenticationConfigController(context, storageType);
    
    if (!add_apis) return;

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("key") || !req->getParams()->isQueryParameterSet("value"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        std::string key;
        std::string value;
        req->getParams()->getQueryParameter("key", key);
        req->getParams()->getQueryParameter("value", value);

        response(res, handleCreate(String(key.c_str()), String(value.c_str())));
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}

        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("key") || !req->getParams()->isQueryParameterSet("value"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string id;
        std::string key;
        std::string value;
        req->getParams()->getQueryParameter("id", id);
        req->getParams()->getQueryParameter("key", key);
        req->getParams()->getQueryParameter("value", value);

        response(res, handleUpdate(String(id.c_str()).toInt(), String(key.c_str()), String(value.c_str())));
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/submit"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_UPDATE) == AuthorizationResults::SUCCESFULL){return;}

        if (!req->getParams()->isQueryParameterSet("key") || !req->getParams()->isQueryParameterSet("value"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        std::string key;
        std::string value;
        req->getParams()->getQueryParameter("key", key);
        req->getParams()->getQueryParameter("value", value);

        response(res, handleSubmit(String(key.c_str()), String(value.c_str())));
    }));
    
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_DELETE) == AuthorizationResults::SUCCESFULL){return;}

        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        std::string id;
        req->getParams()->getQueryParameter("id", id);

        response(res, handleDelete(String(id.c_str()).toInt()));
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_GET) == AuthorizationResults::SUCCESFULL){return;}

        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        std::string query;
        req->getParams()->getQueryParameter("query", query);

        response(res, handleGet(String(query.c_str())));    
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_GET) == AuthorizationResults::SUCCESFULL){return;}

        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        std::string id;
        req->getParams()->getQueryParameter("id", id);

        response(res, handleGetById(String(id.c_str()).toInt()));
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handleGetAll());
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAuthenticayionConfigs"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, DefaultSecurityConfigs::jsonString);
    }));

    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getConfigsJson"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        // if (!context->getSecurity()->checkAuthentication(req, res, Permissions::SYSTEMCONFIG_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, DefaultSecurityConfigs::jsonString);
    }));
}

String AuthenticatioConfigApis::getClassPath()
{
    return String(class_path.c_str());
}


String AuthenticatioConfigApis::callFunction(String functionName, std::map<String, String> parameters)
{
    if (functionName == "create") {
        handleCreate(parameters["key"], parameters["value"]);
        return "OK";
    } else if (functionName == "update") {
        handleUpdate(parameters["id"].toInt(), parameters["key"], parameters["value"]);
        return "OK";
    } else if (functionName == "handleSubmit") {
        handleSubmit(parameters["key"], parameters["value"]);
        return "OK";
    } else if (functionName == "delete") {
        handleDelete(parameters["id"].toInt());
        return "OK";
    } else if (functionName == "get") {
        return handleGet(parameters["query"]);
    } else if (functionName == "getById") {
        return handleGetById(parameters["id"].toInt());
    } else if (functionName == "getAll") {
        return handleGetAll();
    } else {
        return "Error: The function doesn't exist";
    }
}
String AuthenticatioConfigApis::handleCreate(String key, String value) {
    KeyValueEntity *systemConfig = new KeyValueEntity(key, value);
    int id = authenticationConfigController->Add(*systemConfig);
    if (id != -1)
    {
        return String(id);
    }
    
    return CREATE_FAILED_MESSAGE;
}

String AuthenticatioConfigApis::handleUpdate(int id, String key, String value) {
    KeyValueEntity* entity = new KeyValueEntity(id, key, value);
    if(authenticationConfigController->Update(*entity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}

String AuthenticatioConfigApis::handleSubmit(String key, String value) {
    std::vector<KeyValueEntity> systemConfigEntities = authenticationConfigController->Get(KeyValueEntity::COLUMN_KEY + "=" + key);
    if (systemConfigEntities.size() > 0)
    {
        KeyValueEntity* entity = new KeyValueEntity(systemConfigEntities.at(0).id, key, value);
        if(authenticationConfigController->Update(*entity)) return UPDATE_SUCCESFULL_MESSAGE;
        else return UPDATE_FAILED_MESSAGE;
    }
    else
    {
        KeyValueEntity *systemConfig = new KeyValueEntity(key, value);
        int id = authenticationConfigController->Add(*systemConfig);
        if (id != -1) return String(id);        
        return CREATE_FAILED_MESSAGE;
    }
}

String AuthenticatioConfigApis::handleDelete(int id) {
    if(authenticationConfigController->Delete(id)) return DELETE_SUCCESFULL_MESSAGE;
    return DELETE_FAILED_MESSAGE;
}

String AuthenticatioConfigApis::handleGetAll() {
    return authenticationConfigController->GetAllJson();
}

String AuthenticatioConfigApis::handleGet(String query) {
    std::vector<KeyValueEntity> systemConfigEntities = authenticationConfigController->Get(query);
    String result = "[";
    for (size_t i = 0; i < systemConfigEntities.size(); i++)
    {
        result = result + systemConfigEntities.at(i).toString();
    }
    result = result + "]";
    return result;
}

String AuthenticatioConfigApis::handleGetById(int id) {
    KeyValueEntity systemConfig = authenticationConfigController->GetById(id);

    if (systemConfig.id == -1)
    {
        return "no entity";
    }
    else
    {
        return systemConfig.toJson();
    }
}


#endif
