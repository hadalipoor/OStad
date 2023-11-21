#ifndef ROLEPERMISSIONENTITY_H
#define ROLEPERMISSIONENTITY_H

#include "../Entity.h"

class RolePermissionEntity : public Entity {
public:
    static const String COLUMN_ROLEID;
    static const String COLUMN_PERMISSIONID;
    

    int RoleId;
    int PermissionId;
    

    RolePermissionEntity()  : Entity(){}

    RolePermissionEntity(int id, int _RoleId, int _PermissionId) : Entity() {
        this->id = id;
        RoleId = _RoleId;
        PermissionId = _PermissionId;
        

        addColumn(COLUMN_ROLEID, String(RoleId), "int");
        addColumn(COLUMN_PERMISSIONID, String(PermissionId), "int");
        
    }

    RolePermissionEntity(int _RoleId, int _PermissionId) : 
        RolePermissionEntity(0, _RoleId, _PermissionId)  {}

    static RolePermissionEntity fromEntity(Entity entity)
    {
        RolePermissionEntity rolepermissionentity = RolePermissionEntity();
        rolepermissionentity.fromString(entity.toString());
        return rolepermissionentity;
    }

    // Setters and Getters for each field
};

const String RolePermissionEntity::COLUMN_ROLEID = "RoleId";
const String RolePermissionEntity::COLUMN_PERMISSIONID = "PermissionId";


#endif // ROLEPERMISSIONENTITY_H