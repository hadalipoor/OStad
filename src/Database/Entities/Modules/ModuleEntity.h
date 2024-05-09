#ifndef MODULEENTITY_H
#define MODULEENTITY_H

#include "../Entity.h"  // Adjust the include path as necessary
#include <Arduino.h>  // For String type

class ModuleEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MODULE_TYPE;
    static const String COLUMN_DEVICE_ID;
    static const String COLUMN_SERVER_ID;

private:
    String name;
    String moduleType;
    int deviceId;
    int serverId;

public:
    // Default constructor
    ModuleEntity() : Entity(), name(""), moduleType(""), deviceId(0), serverId(0) {}

    // Parameterized constructor
    ModuleEntity(int id, String name, String moduleType, int deviceId, int serverId) : Entity() {
        this->id = id;
        this->name = name;
        this->moduleType = moduleType;
        this->deviceId = deviceId;
        this->serverId = serverId;
        SetValue(COLUMN_NAME, this->name);
        SetValue(COLUMN_MODULE_TYPE, this->moduleType);
        SetValue(COLUMN_DEVICE_ID, String(this->deviceId));
        SetValue(COLUMN_SERVER_ID, String(this->serverId));
    }

    ModuleEntity(int id, String name, String moduleType, int deviceId) : ModuleEntity(id, name, moduleType, deviceId, 0) {}
    ModuleEntity(String name, String moduleType, int deviceId, int serverId) : ModuleEntity(0, name, moduleType, deviceId, serverId) {}
    ModuleEntity(String name, String moduleType, int deviceId) : ModuleEntity(0, name, moduleType, deviceId, 0) {}

    // Destructor
    ~ModuleEntity() {}

    // Getters
    String getName() {
        name = GetValue(COLUMN_NAME);
        return name;
    }

    String getModuleType() {
        moduleType = GetValue(COLUMN_MODULE_TYPE);
        return moduleType;
    }

    int getDeviceId() {
        deviceId = GetValue(COLUMN_DEVICE_ID).toInt();
        return deviceId;
    }

    int getServerId() {
        serverId = GetValue(COLUMN_SERVER_ID).toInt();
        return serverId;
    }

    // Setters
    void setName(String name) {
        SetValue(COLUMN_NAME, name);
        this->name = name;
    }

    void setModuleType(String moduleType) {
        SetValue(COLUMN_MODULE_TYPE, moduleType);
        this->moduleType = moduleType;
    }

    void setDeviceId(int deviceId) {
        SetValue(COLUMN_DEVICE_ID, String(deviceId));
        this->deviceId = deviceId;
    }

    void setServerId(int serverId) {
        SetValue(COLUMN_SERVER_ID, String(serverId));
        this->serverId = serverId;
    }

    static ModuleEntity fromEntity(Entity entity)
    {
        ModuleEntity moduleEntity = ModuleEntity();
        moduleEntity.fromString(entity.toString());
        return moduleEntity;
    }
};

// Static members initialization
const String ModuleEntity::COLUMN_NAME = "Name";
const String ModuleEntity::COLUMN_MODULE_TYPE = "ModuleType";
const String ModuleEntity::COLUMN_DEVICE_ID = "DeviceId";
const String ModuleEntity::COLUMN_SERVER_ID = "ServerId";

#endif // MODULEENTITY_H
