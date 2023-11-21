#ifndef IWiFiManager_h
#define IWiFiManager_h

// 
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <ArduinoJson.h>
#include <vector>
#include "../../Database/Entities/WiFiEntity.h"

struct SSIDInfo {
  String SSID;               // wifi SSID
  String WiFiPassword;       // wifi password
  int WebServerPortHttp;     // http port number for web admin
  int WiFiStrength;          // wifi strength 
  bool isSaved;
};

class IWiFiManager
{
  public:
    virtual void WiFiConnect() = 0;
    virtual void AddSSID(String SSID, String password) = 0;
    virtual void RemoveSSID(String SSID) = 0;
    virtual void GetAvailableSSIDs(std::vector<SSIDInfo> &SSIDInfos) = 0;
    virtual void loop() = 0;
    virtual void configWifiMode() = 0;
    virtual void displayNetworkInfo() = 0;
    virtual void configureAccessPointMode() = 0;
    virtual void configureStationMode() = 0;
    virtual void connectToAvailableNetwork(std::vector<WiFiEntity>& wifiEntities) = 0;
    virtual void connectToNetwork(WiFiEntity& wifiEntity) = 0;
    virtual void waitForConnection() = 0;
    virtual String getConnectedWifi() = 0;
};
#endif