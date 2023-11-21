#ifndef PERMISSIONENTITY_H
#define PERMISSIONENTITY_H

#include "../Entity.h"

class PermissionEntity : public Entity {
public:
    static const String COLUMN_PERMISSIONNAME;
    static const String COLUMN_PERMISSIONGROUP;
    

    String PermissionName;
    String PermissionGroup;
    

    PermissionEntity()  : Entity(){}

    PermissionEntity(int id, String _PermissionName, String _PermissionGroup) : Entity() {
        this->id = id;
        PermissionName = _PermissionName;
        PermissionGroup = _PermissionGroup;
        

        addColumn(COLUMN_PERMISSIONNAME, String(PermissionName), "String");
        addColumn(COLUMN_PERMISSIONGROUP, String(PermissionGroup), "String");
        
    }

    PermissionEntity(String _PermissionName, String _PermissionGroup) : 
        PermissionEntity(0, _PermissionName, _PermissionGroup)  {}

    static PermissionEntity fromEntity(Entity entity)
    {
        PermissionEntity permissionentity = PermissionEntity();
        permissionentity.fromString(entity.toString());
        return permissionentity;
    }

    // Setters and Getters for each field
};

const String PermissionEntity::COLUMN_PERMISSIONNAME = "PermissionName";
const String PermissionEntity::COLUMN_PERMISSIONGROUP = "PermissionGroup";


#endif // PERMISSIONENTITY_H