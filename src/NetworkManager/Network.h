#ifndef Network_H
#define Network_H

#define ASYNC_TCP_SSL_ENABLED 1
#define HTTPS_REQUEST_MAX_REQUEST_LENGTH 1024

#include "INetwork.h"
#include "IPAddress.h"
#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#else
#include <HTTPClient.h>
#endif
#include "../Context.h"
// #include "MeshNetwork/MeshNetworkManager.h"
#include "WiFi/WiFiManager.h"

#include "apis/System/AddSystemApis.h"
#include "apis/Modules/AddModuleApis.h"
#include "apis/Authorization/AddAuthorizationApis.h"
#include "apis/DeviceManager/AddDeviceApis.h"

#include "ApiManager.h"

// The HTTPS Server comes in a separate namespace. For easier use, include it here.
using namespace httpsserver;

struct ServerTaskParams {
    HTTPSServer* httpsServer;
    HTTPServer* httpServer;
    bool https_enabled;
    // Add other members as needed
};

class Network : public INetwork {
private:
    // AsyncWebServer server;
    HTTPServer* httpServer;
    HTTPSServer* httpsServer;
    // HTTPClient http;
    Context* context;
    Receive receive;
    SSLCert cert;

    void configureWebServer();
    void rebootESP(String message);
    // MeshNetworkManager* meshManager;
    WiFiManager* wiFiManager;
    ApiManager* _apiaManager;
    CertificateData _certificateData;
    static void serverTask(ServerTaskParams* params);
    static void serverTaskWrapper(void *params);
    bool isFormatValid(String input);
    bool isNumberOrAsterisk(String segment);
    String inputString = "";     // a string to hold incoming data
    bool stringComplete = false; // whether the string is complete

public:
    Network(Context* context);
    Network(Context* context, CertificateData certificateDate);
    void initialize() override;
    void addApi(ResourceNode* api) override;
    void addUrlNotFound(ResourceNode* api) override;
    void addApis(std::vector<ApiInterface*> apis) override;
    void update() override;
    // IMeshNetworkManager* getMeshManager() override;
    IWiFiManager* getWiFiManager() override;
    HTTPServer& getHTTPServer() override;
    HTTPSServer& getHTTPSServer() override;
    ApiManager* getApiManager() override;

    Receive* getReceive() override;
    void begin();
};

Network::Network(Context* cntxt) : context(cntxt)
{

}

Network::Network(Context* ctxt, CertificateData certificateData): context(ctxt), _certificateData(certificateData)
{

}

void Network::rebootESP(String message) {
    context->getLogger()->log(LogLevel::INFO_LEVEL, LogTitles::SYSTEM_REBOOT, String("Rebooting ESP: " + message));
    ESP.restart();
}

HTTPServer& Network::getHTTPServer()
{
  return *httpServer;
}

HTTPSServer& Network::getHTTPSServer()
{
  return *httpsServer;
}

Receive* Network::getReceive()
{
  return &receive;
}

void Network::configureWebServer() {
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Configuring Web Server ...");
    
    if (_https_enabled)
    {
      
      cert = SSLCert(
                      _certificateData.certificate, _certificateData.certificate_length,
                      _certificateData.privatekey, _certificateData.privateky_length
                    );

      // First, we create the HTTPSServer with the certificate created above
      httpsServer = new HTTPSServer(&cert);
      // Additionally, we create an HTTPServer for unencrypted traffic
    }
    httpServer = new HTTPServer();

    createSystemApis(context);
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "System Apis Created.");    
    createAuthorizationApis(context);
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Authorization Apis Created.");
    createModulesApis(context);
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Module Apis Created.");
    createDeviceApis(context);
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Device Apis Created.");
    context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Web Server Configured.");
}

void Network::addUrlNotFound(ResourceNode* api)
{
  httpServer->setDefaultNode(api);
  if (_https_enabled)
  {
    httpsServer->setDefaultNode(api);
  }
}

void Network::addApi(ResourceNode* api)
{
  
  httpServer->registerNode(api);
  if (_https_enabled)
  {
    httpsServer->registerNode(api);
  }
}

void Network::addApis(std::vector<ApiInterface*> apis)
{
  for (size_t i = 0; i < apis.size(); i++)
  {
    ApiInterface* api = apis.at(i);
    receive.registerClass(String(api->getClassPath().c_str()).substring(1), api);
  } 
}

void Network::begin() {
  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Starting Webserver ...");
  ServerTaskParams* params = new ServerTaskParams;
  params->httpsServer = httpsServer;
  params->httpServer = httpServer;
  params->https_enabled = _https_enabled;
  // Set other members as needed
  xTaskCreatePinnedToCore(serverTaskWrapper, "https443", 6144, params, 1, NULL, ARDUINO_RUNNING_CORE);
}

void Network::serverTaskWrapper(void *params) {
    
    ServerTaskParams* taskParams = static_cast<ServerTaskParams*>(params);
    Network::serverTask(taskParams);
}

void Network::serverTask(ServerTaskParams* params) {
    // Use params->httpsServer and params->httpServer here
    params->httpServer->start();
    if (params->https_enabled)
    {
      params->httpsServer->start();
    }
    

    if (params->httpServer->isRunning())
    {
      Serial.println("HTTP Server is ready.");
      if(params->https_enabled  && params->httpsServer->isRunning())
      {
        Serial.println("HTTPS Server is ready.");
      }

      // "loop()" function of the separate task
      while (true)
      {
        // This call will let the server do its work
        params->httpServer->loop();
        if (params->https_enabled)
        {
          params->httpsServer->loop();
        }

        // Other code would go here...
        delay(1);
      }
    }
    
}

void Network::initialize() {
  _apiaManager = new ApiManager();
  inputString.reserve(200); // reserve 200 bytes for the inputString:

  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Initializing Network ...");

  // meshManager = new MeshNetworkManager(*context);

  wiFiManager = new WiFiManager(context);

  int stationCount = 0;

  // WiFi.mode(WIFI_MODE_AP);
  if(context->getConfig()->getSystemConfig()->get(SystemConfigKey::WIFI_MODE_AP) == "true")
  {
    wiFiManager->configureAccessPointMode();
    stationCount = stationCount + 1;
  }
  if(context->getConfig()->getSystemConfig()->get(SystemConfigKey::WIFI_MODE_WIFI) == "true")
  {
    if(stationCount > 1)
    {
      context->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::SYSTEM_BOOT, "Mesh and AccesPoint are active and Wifi can not run. but it is true.");
      return;
    }
    else if(stationCount == 1)
    {
      // WiFi.mode(WIFI_MODE_STA);
    }
    else
    {
      // WiFi.mode(WIFI_MODE_STA);
    }
    wiFiManager->configureStationMode();
  }
  if(context->getConfig()->getSystemConfig()->get(SystemConfigKey::WIFI_MODE_MESH) == "true")
  {
    // meshManager->initialize();
    stationCount = stationCount + 1;
  }
  else
  {
    if (stationCount == 0)
    {
      wiFiManager->configureAccessPointMode();
    }    
  }
  wiFiManager->displayNetworkInfo();
  configureWebServer();

  context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_BOOT, "Network Initialized.");
}

void Network::update() {
  // Read new bytes (if any) from the serial port:
  while (Serial.available()) {
    char inChar = (char)Serial.read(); // Get the new byte

    // If the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }else{
      inputString += inChar;             // Add it to the inputString
    }
  }
  if (stringComplete) {
    if (isFormatValid(String(inputString)))
    {
      Serial.println(getReceive()->receiveMessage(String(inputString).substring(5)));
    }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  // meshManager->loop();  
    // syncDatabaseLoop();
}

// IMeshNetworkManager* Network::getMeshManager()
// {
//   return meshManager;
// }

IWiFiManager* Network::getWiFiManager()
{
  return wiFiManager;
}

ApiManager* Network::getApiManager()
{
  return _apiaManager;
}

bool Network::isFormatValid(String input) {
    // Check if the string starts with "call "
    if (!input.startsWith("call ")) {
      Serial.print("1");Serial.print(input);
        return false;
    }

    // Remove "call " from the string
    String data = input.substring(5);

    // Split the string by '/'
    int firstSlash = data.indexOf('/');
    int secondSlash = data.lastIndexOf('/');

    // Check if both slashes are found and are not at the start or end of the string
    if (firstSlash == -1 || secondSlash == -1 || firstSlash == 0 || secondSlash == data.length() - 1 || firstSlash == secondSlash) {
      Serial.print("2");
        return false;
    }

    // Extract the segments
    String segment1 = data.substring(0, firstSlash);
    String segment2 = data.substring(firstSlash + 1, secondSlash);
    String segment3 = data.substring(secondSlash + 1);

    // Check if each segment is either a number or a '*'
    return (isNumberOrAsterisk(segment1));
}

bool Network::isNumberOrAsterisk(String segment) {
    if (segment == "*") {
        return true;
    }
    for (char c : segment) {
        if (!isDigit(c)) {
      Serial.print("3");
            return false;
        }
    }
    return true;
}
#endif
