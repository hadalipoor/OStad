#ifndef MODULEENTITY_H
#define MODULEENTITY_H

#include "..\Entity.h"

class ModuleEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MODULE_TYPE;
    static const String COLUMN_CONNECTION_TYPE;
    static const String COLUMN_NODE_ID;
    static const String COLUMN_PIN_NUMBER;

    String Name;
    String ModuleType;
    String ConnectionType;
    int NodeId;
    int PinNumber;

    ModuleEntity() : Entity(){}
    
    ~ModuleEntity(){}

    ModuleEntity(int id, const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId, int pinNumber) : Entity() {
        this->id = id;
        Name = _Name;
        ModuleType = _ModuleType;
        ConnectionType = _ConnectionType;
        NodeId = nodeId;
        PinNumber = pinNumber;
        addColumn(COLUMN_NAME, Name, "string");
        addColumn(COLUMN_MODULE_TYPE, ModuleType, "string");
        addColumn(COLUMN_CONNECTION_TYPE, ConnectionType, "string");
        addColumn(COLUMN_NODE_ID, String(NodeId), "int");
        addColumn(COLUMN_PIN_NUMBER, String(PinNumber), "int");
    }

    ModuleEntity(const String &_Name, const String &_ModuleType, const String &_ConnectionType, int nodeId, int pinNumber) : 
        ModuleEntity(0, _Name, _ModuleType, _ConnectionType, nodeId, pinNumber) {}

    static ModuleEntity fromEntity(Entity entity)
    {
        ModuleEntity moduleEntity = ModuleEntity();
        moduleEntity.fromString(entity.toString());
        return moduleEntity;
    }

    // Setters and Getters for each field

};

const String ModuleEntity::COLUMN_NAME = "Name";
const String ModuleEntity::COLUMN_MODULE_TYPE = "ModuleType";
const String ModuleEntity::COLUMN_CONNECTION_TYPE = "ConnectionType";
const String ModuleEntity::COLUMN_NODE_ID = "NodeId";
const String ModuleEntity::COLUMN_PIN_NUMBER = "PinNumber";

#endif // MODULEENTITY_H
