#ifndef SECURITYQUESTIONTITLEAPIS_h
#define SECURITYQUESTIONTITLEAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/SecurityQuestionTitleController.h"
#include "Permissions.h"

class SecurityQuestionTitleApis : public ApiInterface
{
private:
    AppContext* context;
    SecurityQuestionTitleController* securityquestiontitleController;
    std::string class_path = "/securityquestiontitle";

public:
    SecurityQuestionTitleApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String QuestionTitle);
    String handleupdate(int id, String QuestionTitle);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

SecurityQuestionTitleApis::SecurityQuestionTitleApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    securityquestiontitleController = new SecurityQuestionTitleController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTIONTITLE_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("QuestionTitle"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String QuestionTitle = getQueryParameterString(req, "QuestionTitle");

        response(res, handlecreate(QuestionTitle));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTIONTITLE_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("QuestionTitle"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String QuestionTitle = getQueryParameterString(req, "QuestionTitle");
        
        response(res, handleupdate(id, QuestionTitle));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTIONTITLE_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTIONTITLE_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTIONTITLE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SECURITYQUESTIONTITLE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String SecurityQuestionTitleApis::getClassPath()
{
    return String(class_path.c_str());
}

String SecurityQuestionTitleApis::handlecreate(String QuestionTitle) {
    SecurityQuestionTitleEntity* securityquestiontitleEntity = new SecurityQuestionTitleEntity(QuestionTitle);
    int id = securityquestiontitleController->Add(*securityquestiontitleEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String SecurityQuestionTitleApis::handleupdate(int id, String QuestionTitle) {
    SecurityQuestionTitleEntity* securityquestiontitleEntity = new SecurityQuestionTitleEntity(id, QuestionTitle);
    
    if (securityquestiontitleController->Update(*securityquestiontitleEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String SecurityQuestionTitleApis::handledelete(int id) {
    
    if (securityquestiontitleController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String SecurityQuestionTitleApis::handlegetAll() {
    return securityquestiontitleController->GetAllJson();
}
String SecurityQuestionTitleApis::handlegetById(int id) {
    return securityquestiontitleController->GetById(id).toJson();
}
String SecurityQuestionTitleApis::handleget(String query) {
    return securityquestiontitleController->GetJson(query);
}

String SecurityQuestionTitleApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["QuestionTitle"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["QuestionTitle"]);
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

#endif //SECURITYQUESTIONTITLEApis_h

    