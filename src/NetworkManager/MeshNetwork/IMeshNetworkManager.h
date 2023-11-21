#ifndef IMESHNETWORKMANAGER_H
#define IMESHNETWORKMANAGER_H
#include "Message.h"
#include "Receive.h"
// #include "painlessMesh.h"

typedef std::function<void(Message)> ResponseCallback;
class IMeshNetworkManager
{
public:
    // virtual painlessMesh* getMesh() = 0;
    virtual Receive* getReceive() = 0;
    virtual void setReceive(Receive* receive) = 0;
    virtual void initialize() = 0;
    virtual void loop() = 0;
    // virtual void broadcastMessage(Message message, ResponseCallback callback) = 0;
    virtual void setResponseMessage(Message response) = 0;
    virtual Message* getResponseMessage() = 0;
};
#endif