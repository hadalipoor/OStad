#ifndef RECEIVE_H
#define RECEIVE_H
// Receive.h
#include <map>
#include "Message.h"
#include "../apis/ApiInterface.h"

class Receive {
private:
    std::map<String, ApiInterface*> classes;

public:
    void registerClass(String className, ApiInterface* classInstance) {
        Serial.println(className);
        classes[className] = classInstance;
    }

    String receiveMessage(String messageString) {
        Message message;
        message.fromString(messageString);

        if (classes.count(message.className) > 0) {
            // The class exists
            ApiInterface* classInstance = classes[message.className];
            return classInstance->callFunction(message.functionName, message.parameters);
        } else {
            // The class doesn't exist
            return "Error: The class doesn't exist";
        }
    }
};
#endif