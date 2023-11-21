#ifndef RECENTACTIVITIESAPIS_h
#define RECENTACTIVITIESAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/RecentActivitiesController.h"
#include "Permissions.h"

class RecentActivitiesApis : public ApiInterface
{
private:
    AppContext* context;
    RecentActivitiesController* recentactivitiesController;
    std::string class_path = "/recentactivities";

public:
    RecentActivitiesApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String Title);
    String handleupdate(int id, String Title);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

RecentActivitiesApis::RecentActivitiesApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    recentactivitiesController = new RecentActivitiesController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RECENTACTIVITIES_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("Title"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String Title = getQueryParameterString(req, "Title");

        response(res, handlecreate(Title));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RECENTACTIVITIES_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("Title"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String Title = getQueryParameterString(req, "Title");
        
        response(res, handleupdate(id, Title));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RECENTACTIVITIES_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RECENTACTIVITIES_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RECENTACTIVITIES_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::RECENTACTIVITIES_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String RecentActivitiesApis::getClassPath()
{
    return String(class_path.c_str());
}

String RecentActivitiesApis::handlecreate(String Title) {
    RecentActivitiesEntity* recentactivitiesEntity = new RecentActivitiesEntity(Title);
    int id = recentactivitiesController->Add(*recentactivitiesEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String RecentActivitiesApis::handleupdate(int id, String Title) {
    RecentActivitiesEntity* recentactivitiesEntity = new RecentActivitiesEntity(id, Title);
    
    if (recentactivitiesController->Update(*recentactivitiesEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String RecentActivitiesApis::handledelete(int id) {
    
    if (recentactivitiesController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String RecentActivitiesApis::handlegetAll() {
    return recentactivitiesController->GetAllJson();
}
String RecentActivitiesApis::handlegetById(int id) {
    return recentactivitiesController->GetById(id).toJson();
}
String RecentActivitiesApis::handleget(String query) {
    return recentactivitiesController->GetJson(query);
}

String RecentActivitiesApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handlecreate") {
        return handlecreate(parameters["Title"]);
    }
    if (functionName == "handleupdate") {
        return handleupdate(parameters["id"].toInt(), parameters["Title"]);
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

#endif //RECENTACTIVITIESApis_h

    