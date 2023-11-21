#ifndef ROLEENTITY_H
#define ROLEENTITY_H

#include "../Entity.h"

class RoleEntity : public Entity {
public:
    static const String COLUMN_ROLENAME;
    

    String RoleName;
    

    RoleEntity()  : Entity(){}

    RoleEntity(int id, String _RoleName) : Entity() {
        this->id = id;
        RoleName = _RoleName;
        

        addColumn(COLUMN_ROLENAME, String(RoleName), "String");
        
    }

    RoleEntity(String _RoleName) : 
        RoleEntity(0, _RoleName)  {}

    static RoleEntity fromEntity(Entity entity)
    {
        RoleEntity roleentity = RoleEntity();
        roleentity.fromString(entity.toString());
        return roleentity;
    }

    // Setters and Getters for each field
};

const String RoleEntity::COLUMN_ROLENAME = "RoleName";


#endif // ROLEENTITY_H