#ifndef BASEMODULE_H
#define BASEMODULE_H

#include "ModuleTypes.h"

class BaseModule
{
protected:
    int _module_id;          // ID of module entity in database
    int _id;                 // ID in child module entity in database
    String _name;            // Name of the module
    String _moduleType; // Type of the module, assuming ModuleTypes is an enum
    int _device_id;          // Device ID for the module

public:
    // Constructor
    BaseModule(int module_id, int id, String name, String moduleType, int device_id);

    // Getters and Setters
    int getModuleID();
    void setModuleID(int module_id);

    int getID();
    void setID(int id);

    String getName();
    void setName(String name);

    String getModuleType();
    void setModuleType(String moduleType);

    int getDeviceID();
    void setDeviceID(int device_id);
};

// Constructor
BaseModule::BaseModule(int module_id, int id, String name, String moduleType, int device_id)
: _module_id(module_id), _id(id), _name(name), _moduleType(moduleType), _device_id(device_id)
{
}

// Getters and Setters
int BaseModule::getModuleID() {
    return _module_id;
}

void BaseModule::setModuleID(int module_id) {
    _module_id = module_id;
}

int BaseModule::getID() {
    return _id;
}

void BaseModule::setID(int id) {
    _id = id;
}

String BaseModule::getName() {
    return _name;
}

void BaseModule::setName(String name) {
    _name = name;
}

String BaseModule::getModuleType() {
    return _moduleType;
}

void BaseModule::setModuleType(String moduleType) {
    _moduleType = moduleType;
}

int BaseModule::getDeviceID() {
    return _device_id;
}

void BaseModule::setDeviceID(int device_id) {
    _device_id = device_id;
}

#endif // BASEMODULE_H