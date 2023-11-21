#ifndef ClockApis_h
#define ClockApis_h

#include "../../../Context.h"
#include "SystemPermissions.h"

class ClockApis : public ApiInterface {
public:
    // Constructor
    ClockApis(Context* context, bool add_apis);


    // APIs
    EBPDateTime now();
    JalaliDateTime nowJalali();
    void adjust(const EBPDateTime& dateTime);
    void syncTimeWithServer();

    String callFunction(String functionName, std::map<String, String> parameters);

private:
    std::string class_path = "/clock";
    String getClassPath() override;
    Context* context;
};

ClockApis::ClockApis(Context* cntxt, bool add_apis) : context(cntxt) {
    if (!add_apis) return;

    // Add API for getting the current time
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/now"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::CLOCK_GET) == AuthorizationResults::SUCCESFULL){return;}
        EBPDateTime currentTime = this->now();
        String output = currentTime.toDateTimeString();
        response(res, output);
    }));

    // Add API for getting the current Jalali time
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/nowJalali"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::CLOCK_GET) == AuthorizationResults::SUCCESFULL){return;}
        JalaliDateTime currentJalaliTime = this->nowJalali();
        response(res, currentJalaliTime.toDateTimeString());
    }));

    // Add API for adjusting the time
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/adjustTime"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::CLOCK_SET) == AuthorizationResults::SUCCESFULL){return;}
        
        if (!req->getParams()->isQueryParameterSet("date"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        // Extract dateTime from the request
        EBPDateTime dateTime = EBPDateTime(getQueryParameterint(req, "date")); // Assume this object can be constructed from the request

        this->adjust(dateTime);

        response(res, 200, "text/plain", "Time adjusted successfully");
    }));

    // Add API for syncing time with the server
    context->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/syncTime"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->getSecurity()->checkAuthentication(req, res, SystemPermissions::CLOCK_SET) == AuthorizationResults::SUCCESFULL){return;}
        this->syncTimeWithServer();
        response(res, 200, "text/plain", "Time synced with server successfully");
    }));
}

String ClockApis::getClassPath()
{
    return String(class_path.c_str());
}

EBPDateTime ClockApis::now() {
    return context->getClock()->now();
}

JalaliDateTime ClockApis::nowJalali() {
    return context->getClock()->nowJalali();
}

void ClockApis::adjust(const EBPDateTime& dateTime) {
    context->getClock()->adjust(dateTime);
}

void ClockApis::syncTimeWithServer() {
    context->getClock()->syncTimeWithServer();
}

String ClockApis::callFunction(String functionName, std::map<String, String> parameters) {
    // Handling 'now' function call
    if (functionName == "now") {
        return now().toDateTimeString();
    }

    // Handling 'nowJalali' function call
    if (functionName == "nowJalali") {
        return nowJalali().toDateTimeString();
    }

    // Handling 'adjust' function call
    if (functionName == "adjust") {
        if (!parameters.count("date")) {
            return "Missing 'date' parameter for adjust function";
        }
        EBPDateTime dateTime = EBPDateTime(parameters["date"]); // Convert the string to EBPDateTime
        adjust(dateTime);
        return "Time adjusted successfully";
    }

    // Handling 'syncTimeWithServer' function call
    if (functionName == "syncTimeWithServer") {
        syncTimeWithServer();
        return "Time synced with server successfully";
    }

    // If the function name does not match any known function
    return String("No such function: ") + functionName;
}

#endif
