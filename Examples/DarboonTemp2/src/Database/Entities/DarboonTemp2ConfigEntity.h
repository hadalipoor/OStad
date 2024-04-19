#ifndef DARBOONTEMP2CONFIGENTITY_H
#define DARBOONTEMP2CONFIGENTITY_H

#include <OStad.h>

class DarboonTemp2ConfigEntity : public Entity {
public:
    static const String COLUMN_KEY;
    static const String COLUMN_VALUE;
    

    String Key;
    String Value;
    

    DarboonTemp2ConfigEntity()  : Entity(){}

    DarboonTemp2ConfigEntity(int id, String _Key, String _Value) : Entity() {
        this->id = id;
        Key = _Key;
        Value = _Value;
        

        addColumn(COLUMN_KEY, String(Key), "String");
        addColumn(COLUMN_VALUE, String(Value), "String");
        
    }

    DarboonTemp2ConfigEntity(String _Key, String _Value) : 
        DarboonTemp2ConfigEntity(0, _Key, _Value)  {}

    static DarboonTemp2ConfigEntity fromEntity(Entity entity)
    {
        DarboonTemp2ConfigEntity darboontemp2configentity = DarboonTemp2ConfigEntity();
        darboontemp2configentity.fromString(entity.toString());
        return darboontemp2configentity;
    }

    // Setters and Getters for each field
};

const String DarboonTemp2ConfigEntity::COLUMN_KEY = "Key";
const String DarboonTemp2ConfigEntity::COLUMN_VALUE = "Value";


#endif // DARBOONTEMP2CONFIGENTITY_H