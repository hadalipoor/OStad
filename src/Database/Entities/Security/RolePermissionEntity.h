#ifndef ROLEPERMISSIONENTITY_H
#define ROLEPERMISSIONENTITY_H

#include "../Entity.h"

class RolePermissionEntity : public Entity {
public:
    static const String COLUMN_ROLEID;
    static const String COLUMN_PERMISSIONID;

private:
    int roleId;
    int permissionId;

public:
    RolePermissionEntity() : Entity(), roleId(0), permissionId(0) {}

    RolePermissionEntity(int id, int _RoleId, int _PermissionId) : Entity() {
        this->id = id;
        this->roleId = _RoleId;
        this->permissionId = _PermissionId;
        SetValue(COLUMN_ROLEID, String(this->roleId));
        SetValue(COLUMN_PERMISSIONID, String(this->permissionId));
    }

    RolePermissionEntity(int _RoleId, int _PermissionId) : 
        RolePermissionEntity(0, _RoleId, _PermissionId) {}

    static RolePermissionEntity fromEntity(Entity entity) {
        RolePermissionEntity rolepermissionentity = RolePermissionEntity();
        rolepermissionentity.fromString(entity.toString());
        return rolepermissionentity;
    }

    // Getters
    int getRoleId() {
        roleId = GetValue(COLUMN_ROLEID).toInt();
        return roleId;
    }

    int getPermissionId() {
        permissionId = GetValue(COLUMN_PERMISSIONID).toInt();
        return permissionId;
    }

    // Setters
    void setRoleId(int value) {
        roleId = value;
        SetValue(COLUMN_ROLEID, String(roleId));
    }

    void setPermissionId(int value) {
        permissionId = value;
        SetValue(COLUMN_PERMISSIONID, String(permissionId));
    }
};

const String RolePermissionEntity::COLUMN_ROLEID = "RoleId";
const String RolePermissionEntity::COLUMN_PERMISSIONID = "PermissionId";

#endif // ROLEPERMISSIONENTITY_H
