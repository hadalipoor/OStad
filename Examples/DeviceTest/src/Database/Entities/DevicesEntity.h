#ifndef DEVICESENTITY_H
#define DEVICESENTITY_H

#include <OStad.h>

class DevicesEntity : public Entity {
public:
    static const String COLUMN_DEVICETYPE;
    static const String COLUMN_CHIPID;
    static const String COLUMN_IP;
    static const String COLUMN_NAME;
    static const String COLUMN_PARENTCHIPID;
    static const String COLUMN_APSSID;
    static const String COLUMN_APPASSWORD;
    

    String DeviceType;
    String ChipId;
    String IP;
    String Name;
    String ParentChipId;
    String ApSSID;
    String ApPassword;
    

    DevicesEntity()  : Entity(){}

    DevicesEntity(int id, String _DeviceType, String _ChipId, String _IP, String _Name, String _ParentChipId, String _ApSSID, String _ApPassword) : Entity() {
        this->id = id;
        DeviceType = _DeviceType;
        ChipId = _ChipId;
        IP = _IP;
        Name = _Name;
        ParentChipId = _ParentChipId;
        ApSSID = _ApSSID;
        ApPassword = _ApPassword;
        

        addColumn(COLUMN_DEVICETYPE, String(DeviceType), "String");
        addColumn(COLUMN_CHIPID, String(ChipId), "String");
        addColumn(COLUMN_IP, String(IP), "String");
        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_PARENTCHIPID, String(ParentChipId), "String");
        addColumn(COLUMN_APSSID, String(ApSSID), "String");
        addColumn(COLUMN_APPASSWORD, String(ApPassword), "String");
        
    }

    DevicesEntity(String _DeviceType, String _ChipId, String _IP, String _Name, String _ParentChipId, String _ApSSID, String _ApPassword) : 
        DevicesEntity(0, _DeviceType, _ChipId, _IP, _Name, _ParentChipId, _ApSSID, _ApPassword)  {}

    static DevicesEntity fromEntity(Entity entity)
    {
        DevicesEntity devicesentity = DevicesEntity();
        devicesentity.fromString(entity.toString());
        return devicesentity;
    }

    // Setters and Getters for each field
};

const String DevicesEntity::COLUMN_DEVICETYPE = "DeviceType";
const String DevicesEntity::COLUMN_CHIPID = "ChipId";
const String DevicesEntity::COLUMN_IP = "IP";
const String DevicesEntity::COLUMN_NAME = "Name";
const String DevicesEntity::COLUMN_PARENTCHIPID = "ParentChipId";
const String DevicesEntity::COLUMN_APSSID = "ApSSID";
const String DevicesEntity::COLUMN_APPASSWORD = "ApPassword";


#endif // DEVICESENTITY_H