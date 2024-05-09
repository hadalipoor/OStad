#ifndef PERMISSIONENTITY_H
#define PERMISSIONENTITY_H

#include "../Entity.h"

class PermissionEntity : public Entity {
public:
    static const String COLUMN_PERMISSIONNAME;
    static const String COLUMN_PERMISSIONGROUP;

private:
    String permissionName;
    String permissionGroup;

public:
    PermissionEntity() : Entity(), permissionName(""), permissionGroup("") {}

    PermissionEntity(int id, String _PermissionName, String _PermissionGroup) : Entity() {
        this->id = id;
        this->permissionName = _PermissionName;
        this->permissionGroup = _PermissionGroup;
        SetValue(COLUMN_PERMISSIONNAME, this->permissionName);
        SetValue(COLUMN_PERMISSIONGROUP, this->permissionGroup);
    }

    PermissionEntity(String _PermissionName, String _PermissionGroup) : 
        PermissionEntity(0, _PermissionName, _PermissionGroup) {}

    static PermissionEntity fromEntity(Entity entity) {
        PermissionEntity permissionentity = PermissionEntity();
        permissionentity.fromString(entity.toString());
        return permissionentity;
    }

    // Getters
    String getPermissionName() {
        permissionName = GetValue(COLUMN_PERMISSIONNAME);
        return permissionName;
    }

    String getPermissionGroup() {
        permissionGroup = GetValue(COLUMN_PERMISSIONGROUP);
        return permissionGroup;
    }

    // Setters
    void setPermissionName(String value) {
        permissionName = value;
        SetValue(COLUMN_PERMISSIONNAME, permissionName);
    }

    void setPermissionGroup(String value) {
        permissionGroup = value;
        SetValue(COLUMN_PERMISSIONGROUP, permissionGroup);
    }
};

const String PermissionEntity::COLUMN_PERMISSIONNAME = "PermissionName";
const String PermissionEntity::COLUMN_PERMISSIONGROUP = "PermissionGroup";

#endif // PERMISSIONENTITY_H
