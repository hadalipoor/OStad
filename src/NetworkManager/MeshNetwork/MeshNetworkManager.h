#ifndef MESHNETWORKMANAGER_H
#define MESHNETWORKMANAGER_H

// #include "painlessMesh.h"
#include "../../Context.h"
#include "../../Config/System/SystemConfigKeys.h"
#include "Message.h"
#include "Receive.h"
#include "IMeshNetworkManager.h"
class MeshNetworkManager : public IMeshNetworkManager
{
private:
    const char*   MESH_PREFIX = "whateverYouLike";
    const char*   MESH_PASSWORD = "somethingSneaky";
    const uint16_t   MESH_PORT =  5555;
    const char* HOSTNAME = "HTTP_BRIDGE";
    Context context;
    int32_t start_millis;
    bool initialized;
    Message responseMessage;
    // typedef void (*ResponseCallback)(Message);
    // ResponseCallback responseCallback;
    // painlessMesh mesh;
    Receive receive;
public:
    // static MeshNetworkManager* MeshManagerinstance;  // Static pointer to the class MeshManagerinstance

    MeshNetworkManager(Context &context);
    void initialize() override;
    static void receivedCallback(const uint32_t &from, const String &msg );
    void loop() override;
    // void broadcastMessage(Message message, ResponseCallback callback) override;
    void setResponseMessage(Message response) override;
    Message* getResponseMessage() override;
    // painlessMesh* getMesh() override;
    Receive* getReceive() override;
    void setReceive(Receive* receive) override;
};

// MeshNetworkManager* MeshNetworkManager::MeshManagerinstance = nullptr;

MeshNetworkManager::MeshNetworkManager(Context &context): context(context)
{
    // MeshManagerinstance = this;  // Set the static pointer to this MeshManagerinstance
    initialized = false;
}
void MeshNetworkManager::initialize()
{
    // mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );
    // mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT );
    // mesh.onReceive(&receivedCallback);
    // mesh.setHostname(HOSTNAME);

    // String meshRootStr = context.getConfig()->get(SystemConfigKey::MESH_ROOT);
    // bool meshRoot = (meshRootStr == "true");
    // mesh.setRoot(meshRoot);
    // mesh.setContainsRoot(true);
    // start_millis = millis();
    // initialized = true;
}

void MeshNetworkManager::receivedCallback(const uint32_t &from, const String &msg ) {
    // Message message;
    // message.fromString(msg);
    // painlessMesh& mesh = MeshManagerinstance->mesh;  // Use the static pointer to access the mesh
    // Receive& receive = MeshManagerinstance->receive;  // Use the static pointer to access the receive
    // if (message.nodeId == mesh.getNodeId() || message.nodeId == 0)
    // {
    //     if(message.responseMessage.length() > 0)
    //     {
    //         MeshManagerinstance->setResponseMessage(message);
    //         if (MeshManagerinstance->responseCallback) {
    //             MeshManagerinstance->responseCallback(message);  // Call the callback with the response
    //         }
    //         return;
    //     }        
    //     Message responseMessage;
    //     responseMessage.responseMessage = receive.receiveMessage(msg);
    //     MeshManagerinstance->broadcastMessage(responseMessage, nullptr);
    // }

    // Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
}

void MeshNetworkManager::setResponseMessage(Message response)
{
    responseMessage = response;
}

Message* MeshNetworkManager::getResponseMessage()
{
    Message rm = responseMessage;
    responseMessage.responseMessage = "";
    return &rm;
}

void MeshNetworkManager::loop()
{

    // if (context.getConfig()->get(SystemConfigKey::WIFI_MODE_MESH) != "true")
    // {
    //     return;
    // }
    // if (!initialized)
    // {
    //     context.getErrorHandler()->handleError("MeshNetwork is not initialized");
    //     return;
    // }
    
    // // mesh.update();
    // if (millis() - start_millis > 5000)
    // {
    // start_millis = millis();
    // Serial.print("My AP IP is ");
    // Serial.print(IPAddress(mesh.getAPIP()).toString());
    // Serial.print(" and Station IP is ");
    // Serial.println(IPAddress(mesh.getStationIP()).toString());
    // }

}

// void MeshNetworkManager::broadcastMessage(Message message, ResponseCallback callback) {
//     String messageString = message.toString();
//     mesh.sendBroadcast(messageString);
//     responseCallback = callback;  // Save the callback for later
// }

// painlessMesh* MeshNetworkManager::getMesh()
// {
//     return &mesh;
// }

Receive* MeshNetworkManager::getReceive()
{
    return &receive;
}

void MeshNetworkManager::setReceive(Receive* receive)
{
    receive = receive;
}
#endif
