#ifndef INETWORK
#define INETWORK
#include <HTTPS_Server_Generic.h>
// #include "MeshNetwork/IMeshNetworkManager.h"
#include "WiFi/IWiFiManager.h"
#include "MeshNetwork/Receive.h"
#include "LambdaResourceNode.h"
#include "ApiManager.h"

using namespace httpsserver;

struct CertificateData{
    unsigned char* certificate;
    uint16_t certificate_length;
    unsigned char* privatekey;
    uint16_t privateky_length;
};

class INetwork {
public:
    virtual void initialize() = 0;
    virtual void addApis(std::vector<ApiInterface*> apis) = 0;
    virtual void update() = 0;
    // virtual IMeshNetworkManager* getMeshManager() = 0;
    virtual IWiFiManager* getWiFiManager() = 0;
    virtual HTTPServer& getHTTPServer() = 0;
    virtual HTTPSServer& getHTTPSServer() = 0;
    virtual void addApi(ResourceNode* api) = 0;
    virtual void addUrlNotFound(ResourceNode* api) = 0;
    virtual Receive* getReceive() = 0;
    virtual ApiManager* getApiManager() = 0;

};

#endif