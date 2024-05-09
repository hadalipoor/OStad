#ifndef APIINTERFACE_H
#define APIINTERFACE_H

// ApiInterface.h
#include <map>
#include <string>
#include <sstream>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPS_Server_Generic.h>
#include "../../FileManager/IEBPFile.h"
#include "../../Clock/EBPDateTime.h"

using namespace httpsserver;

class ApiInterface {
public:
    virtual String callFunction(String functionName, std::map<String, String> parameters) = 0;
    virtual String getClassPath() = 0;

    static const String MISSING_INPUT_PARAMS_MESSAGE;
    static const String WRONG_INPUT_PARAMS_FORMAT_MESSAGE;
    static const String CREATE_SUCCESFULL_MESSAGE;
    static const String CREATE_FAILED_MESSAGE;
    static const String DELETE_FAILED_MESSAGE;
    static const String DELETE_SUCCESFULL_MESSAGE;
    static const String UPDATE_SUCCESFULL_MESSAGE;
    static const String UPDATE_FAILED_MESSAGE;
    static const String NO_FUNCTION_MESSAGE;
    static const String PAGE_NOT_FOUND_MESSAGE;
};

const String ApiInterface::MISSING_INPUT_PARAMS_MESSAGE = "missing some input params in your request";
const String ApiInterface::WRONG_INPUT_PARAMS_FORMAT_MESSAGE = "some input params format in your request is not correct";
const String ApiInterface::CREATE_FAILED_MESSAGE = "Create Operation Failed!";
const String ApiInterface::CREATE_SUCCESFULL_MESSAGE = "Create Succesfull";
const String ApiInterface::DELETE_FAILED_MESSAGE = "Delete Operation Failed!";
const String ApiInterface::DELETE_SUCCESFULL_MESSAGE = "Delete Succesfull";
const String ApiInterface::UPDATE_SUCCESFULL_MESSAGE = "Update Succesfull";
const String ApiInterface::UPDATE_FAILED_MESSAGE = "Update Operation Failed!";
const String ApiInterface::NO_FUNCTION_MESSAGE = "There is no function named ";
const String ApiInterface::PAGE_NOT_FOUND_MESSAGE = "<!DOCTYPE html><html><body style=\"background-color:black; color:white; text-align:center; height:100vh; display:flex; align-items:center; justify-content:center; margin:0;\"><h1>Page Not Found!</h1></body></html>";


void response(HTTPResponse * res, int status_code, String status_text, String content_type, String response_text)
{
    res->setStatusCode(status_code);
    res->setStatusText(status_text.c_str());
    res->setHeader("Content-Type", content_type.c_str());
    res->println(response_text);
}

void response(HTTPResponse * res, int status_code, String content_type, String response_text)
{
    res->setStatusCode(status_code);
    res->setStatusText(String(status_code).c_str());
    res->setHeader("Content-Type", content_type.c_str());
    res->println(response_text);
}

void response(HTTPResponse * res, int status_code, String response_text)
{
    res->setStatusCode(status_code);
    res->setStatusText(String(status_code).c_str());
    res->setHeader("Content-Type", "text/html");
    res->println(response_text);
}

void response(HTTPResponse * res, String response_text)
{
    res->setStatusCode(200);
    res->setStatusText("Succesfull");
    res->setHeader("Content-Type", "text/html");
    res->println(response_text);
}

String jsonResponse(bool success, String description)
{
    return "{\"success\":\"" + String(success ? "true" : "false") + "\", \"description\":\""+ description +"\"}";
}

String getBodyString(HTTPRequest *req)
{
    byte buffer[1024];
    String body = "";  // Initialize an empty String to accumulate the data
    // Continue reading until the request is complete
    while (!(req->requestComplete()))
    {
        // Read bytes into the buffer
        size_t s = req->readBytes(buffer, 1024);
        // Append the read bytes to the String. This assumes the bytes are ASCII characters
        if (s > 0) {
            body += String((char*)buffer);  // Convert bytes to String and concatenate
        }
    }
    return body;  // Return the complete String containing the request body
}

String getItemInBody(String body, String item)
{
    DynamicJsonDocument doc(1024);  // Create a JSON document with a suitable size
    DeserializationError error = deserializeJson(doc, body);  // Parse the JSON body

    if (error) {  // Check if there was an error in parsing
        return "";  // Return empty string if there is an error
    }

    // Use containsKey to check if the item exists and return its value if it does
    if (doc.containsKey(item)) {
        JsonVariant var = doc[item];
        if (var.is<String>()) {  // Check if the item is a string and return it
            return var.as<String>();
        } else {  // For non-string types, serialize them back to a String
            String result;
            serializeJson(var, result);  // Convert JSON variant to string if it is not a simple string
            return result;
        }
    }

    return "";  // Return empty string if item is not found
}

bool isItemInBody(String body, String item)
{
    DynamicJsonDocument doc(1024);  // Create a JSON document with enough size
    DeserializationError error = deserializeJson(doc, body);  // Parse the JSON body

    if (error) {  // Check if there was an error in parsing
        Serial.println("error in isItemInBody");
        return false;
    }
    // Check if the item exists in the JSON document
    return doc.containsKey(item);
}

String getQueryParameterString(HTTPRequest * req, String parameter)
{
    std::string output;
    
    req->getParams()->getQueryParameter(parameter.c_str(), output);
    return String(output.c_str());
}

int getQueryParameterint(HTTPRequest * req, String parameter)
{
    std::string output;
    req->getParams()->getQueryParameter(parameter.c_str(), output);
    
    int number;
    std::stringstream ss(output);

    if (ss >> number && ss.eof()) {
        // Successfully converted to an int
        return number;
    } else {
        // Conversion failed, return -9999
        return -9999;
    }
}

EBPDateTime getQueryParameterEBPDateTime(HTTPRequest * req, String parameter)
{
    String strDateTime = getQueryParameterString(req, parameter);
    return EBPDateTime(strDateTime);
}

void DownloadFile(HTTPResponse *res, String filename, String contentType, StorageType storageType) {
  // Set content type based on file extension
//   std::string _contentType = "application/octet-stream"; // Default content type
    std::string _contentType ; // Default content type
    if (contentType == "")
    {
        // Determine content type based on file extension
        if (filename.endsWith(".html")) {
            _contentType = "text/html";
        } else if (filename.endsWith(".css")) {
            _contentType = "text/css";
        } else if (filename.endsWith(".js")) {
            _contentType = "text/javascript";
        } else if (filename.endsWith(".json")) {
            _contentType = "application/json";
        } else if (filename.endsWith(".png")) {
            _contentType = "image/png";
        } else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) {
            _contentType = "image/jpeg";
        } else if (filename.endsWith(".svg")) {
            _contentType = "image/svg+xml";
        } else if (filename.endsWith(".gif")) {
            _contentType = "image/gif";
        } else if (filename.endsWith(".pdf")) {
            _contentType = "application/pdf";
        } else if (filename.endsWith(".xml")) {
            _contentType = "application/xml";
        } else if (filename.endsWith(".txt") || filename.endsWith(".db")) {
            _contentType = "text/plain";
        } else if (filename.endsWith(".mp3")) {
            _contentType = "audio/mpeg";
        } else if (filename.endsWith(".mp4")) {
            _contentType = "video/mp4";
        } else if (filename != "") {
            // Set a default content type for unknown file types
            _contentType = "text/html";
        } 
    } else {
        // if contentType is filled by user, add it to header content type
        _contentType = std::string(contentType.c_str());
    }
  
    File file;
    if (storageType == StorageType::SPIFFS_TYPE) {
        file = LittleFS.open(filename.c_str(), "r");
    } else if (storageType == StorageType::SD_TYPE) {
        file = SD.open(filename.c_str(), "r");
    }

  // Set response headers
//   res->setHeader("Content-Disposition", "attachment; filename=\"" + std::string(filename.c_str()) + "\"");
    res->setHeader("Content-Type", _contentType);
//   res->setHeader("Content-Length", std::string(String(file.size()).c_str()));

    // Send the file content
    uint8_t buffer[256];
    size_t bytesRead;

    while ((bytesRead = file.read(buffer, sizeof(buffer))) > 0) {
        res->write(buffer, bytesRead);
    }

    // Close the file
    file.close();
}

void RedirectUrl(HTTPResponse * res, String url)
{
    res->setStatusCode(303);
    res->setStatusText("See Other");
    res->setHeader("Location", url.c_str());
    res->println("Redirecting...");    
}
#endif