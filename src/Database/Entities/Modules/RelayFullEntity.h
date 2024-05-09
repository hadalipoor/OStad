#ifndef RELAYFULLENTITY_H
#define RELAYFULLENTITY_H

#include "..\Entity.h"

class RelayFullEntity {
public:
    int id;
    int ModuleId;
    String Name;
    String ModuleType;
    int DeviceId;
    int PinNumber;
    bool NormallyOpen;
    int ServerId;

    RelayFullEntity() {}

    RelayFullEntity(int id, int moduleId, const String &_Name, const String &_ModuleType, int deviceId,
                    int pinNumber, bool normallyOpen, int serverId) {
        this->id = id;
        NormallyOpen = normallyOpen;
        ModuleId = moduleId;
        Name = _Name;
        ModuleType = _ModuleType;
        DeviceId = deviceId;
        PinNumber = pinNumber;
        ServerId = serverId;
    }

    String getJsonString() {
        String json = "{";
        json += "\"Id\": " + String(id) + ", ";
        json += "\"ModuleId\": " + String(ModuleId) + ", ";
        json += "\"Name\": \"" + Name + "\", ";
        json += "\"ModuleType\": \"" + ModuleType + "\", ";
        json += "\"DeviceId\": " + String(DeviceId) + ", ";
        json += "\"PinNumber\": " + String(PinNumber) + ", ";
        json += "\"NormallyOpen\": " + String(NormallyOpen ? "true" : "false") + ", ";
        json += "\"ServerId\": " + String(ServerId);
        json += "}";
        return json;
    }
};

#endif // RELAYFULLENTITY_H
