#ifndef ROLEENTITY_H
#define ROLEENTITY_H

#include "../Entity.h"

class RoleEntity : public Entity {
public:
    static const String COLUMN_ROLENAME;

private:
    String roleName;

public:
    RoleEntity() : Entity(), roleName("") {}

    RoleEntity(int id, String _RoleName) : Entity() {
        this->id = id;
        this->roleName = _RoleName;
        SetValue(COLUMN_ROLENAME, this->roleName);
    }

    RoleEntity(String _RoleName) : 
        RoleEntity(0, _RoleName) {}

    static RoleEntity fromEntity(Entity entity) {
        RoleEntity roleentity = RoleEntity();
        roleentity.fromString(entity.toString());
        return roleentity;
    }

    // Getters
    String getRoleName() {
        roleName = GetValue(COLUMN_ROLENAME);
        return roleName;
    }

    // Setters
    void setRoleName(String value) {
        roleName = value;
        SetValue(COLUMN_ROLENAME, roleName);
    }
};

const String RoleEntity::COLUMN_ROLENAME = "RoleName";

#endif // ROLEENTITY_H
