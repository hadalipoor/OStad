#ifndef MODULEENTITY_H
#define MODULEENTITY_H

#include "../Entity.h"

class ModuleEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MODULETYPE;
    static const String COLUMN_DEVICEID;
    static const String COLUMN_SERVERID;
    
private:
    String _Name;
    String _ModuleType;
    int _DeviceId;
    int _ServerId;
    

public:
    ModuleEntity()  : Entity(){}

    ModuleEntity(int id, String Name, String ModuleType, int DeviceId, int ServerId) : Entity() {
        this->id = id;
        _Name = Name;
        _ModuleType = ModuleType;
        _DeviceId = DeviceId;
        _ServerId = ServerId;
        

        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_MODULETYPE, String(ModuleType), "String");
        addColumn(COLUMN_DEVICEID, String(DeviceId), "int");
        addColumn(COLUMN_SERVERID, String(ServerId), "int");
        
    }

    ModuleEntity(String Name, String ModuleType, int DeviceId, int ServerId) : 
        ModuleEntity(0, _Name, _ModuleType, _DeviceId, _ServerId)  {}

    static ModuleEntity fromEntity(Entity entity)
    {
        ModuleEntity moduleentity = ModuleEntity();
        moduleentity.fromString(entity.toString());
        return moduleentity;
    }

    // Getters for each field
    String getName() {
        return _Name;
    }
    String getModuleType() {
        return _ModuleType;
    }
    int getDeviceId() {
        return _DeviceId;
    }
    int getServerId() {
        return _ServerId;
    }
    
    
    // Setters for each field
    void setName(String Name) {
        SetValue(COLUMN_NAME, String(Name));
        _Name = Name;
    }
    void setModuleType(String ModuleType) {
        SetValue(COLUMN_MODULETYPE, String(ModuleType));
        _ModuleType = ModuleType;
    }
    void setDeviceId(int DeviceId) {
        SetValue(COLUMN_DEVICEID, String(DeviceId));
        _DeviceId = DeviceId;
    }
    void setServerId(int ServerId) {
        SetValue(COLUMN_SERVERID, String(ServerId));
        _ServerId = ServerId;
    }
    
};

const String ModuleEntity::COLUMN_NAME = "Name";
const String ModuleEntity::COLUMN_MODULETYPE = "ModuleType";
const String ModuleEntity::COLUMN_DEVICEID = "DeviceId";
const String ModuleEntity::COLUMN_SERVERID = "ServerId";


#endif // MODULEENTITY_H