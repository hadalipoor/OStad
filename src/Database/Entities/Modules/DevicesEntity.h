#ifndef DEVICESENTITY_H
#define DEVICESENTITY_H

#include "../Entity.h"

class DevicesEntity : public Entity {
public:
    static const String COLUMN_DEVICETYPE;
    static const String COLUMN_CHIPID;
    static const String COLUMN_IP;
    static const String COLUMN_NAME;
    static const String COLUMN_PARENTCHIPID;
    static const String COLUMN_APSSID;
    static const String COLUMN_APPASSWORD;
    
private:
    String _DeviceType;
    String _ChipId;
    String _IP;
    String _Name;
    String _ParentChipId;
    String _ApSSID;
    String _ApPassword;
    

public:
    DevicesEntity()  : Entity(){}

    DevicesEntity(int id, String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword) : Entity() {
        this->id = id;
        _DeviceType = DeviceType;
        _ChipId = ChipId;
        _IP = IP;
        _Name = Name;
        _ParentChipId = ParentChipId;
        _ApSSID = ApSSID;
        _ApPassword = ApPassword;
        

        addColumn(COLUMN_DEVICETYPE, String(DeviceType), "String");
        addColumn(COLUMN_CHIPID, String(ChipId), "String");
        addColumn(COLUMN_IP, String(IP), "String");
        addColumn(COLUMN_NAME, String(Name), "String");
        addColumn(COLUMN_PARENTCHIPID, String(ParentChipId), "String");
        addColumn(COLUMN_APSSID, String(ApSSID), "String");
        addColumn(COLUMN_APPASSWORD, String(ApPassword), "String");
        
    }

    DevicesEntity(String DeviceType, String ChipId, String IP, String Name, String ParentChipId, String ApSSID, String ApPassword) : 
        DevicesEntity(0, _DeviceType, _ChipId, _IP, _Name, _ParentChipId, _ApSSID, _ApPassword)  {}

    static DevicesEntity fromEntity(Entity entity)
    {
        DevicesEntity devicesentity = DevicesEntity();
        devicesentity.fromString(entity.toString());
        return devicesentity;
    }

    // Getters for each field
    String getDeviceType() {
        return _DeviceType;
    }
    String getChipId() {
        return _ChipId;
    }
    String getIP() {
        return _IP;
    }
    String getName() {
        return _Name;
    }
    String getParentChipId() {
        return _ParentChipId;
    }
    String getApSSID() {
        return _ApSSID;
    }
    String getApPassword() {
        return _ApPassword;
    }
    
    
    // Setters for each field
    void setDeviceType(String DeviceType) {
        SetValue(COLUMN_DEVICETYPE, String(DeviceType));
        _DeviceType = DeviceType;
    }
    void setChipId(String ChipId) {
        SetValue(COLUMN_CHIPID, String(ChipId));
        _ChipId = ChipId;
    }
    void setIP(String IP) {
        SetValue(COLUMN_IP, String(IP));
        _IP = IP;
    }
    void setName(String Name) {
        SetValue(COLUMN_NAME, String(Name));
        _Name = Name;
    }
    void setParentChipId(String ParentChipId) {
        SetValue(COLUMN_PARENTCHIPID, String(ParentChipId));
        _ParentChipId = ParentChipId;
    }
    void setApSSID(String ApSSID) {
        SetValue(COLUMN_APSSID, String(ApSSID));
        _ApSSID = ApSSID;
    }
    void setApPassword(String ApPassword) {
        SetValue(COLUMN_APPASSWORD, String(ApPassword));
        _ApPassword = ApPassword;
    }
    
};

const String DevicesEntity::COLUMN_DEVICETYPE = "DeviceType";
const String DevicesEntity::COLUMN_CHIPID = "ChipId";
const String DevicesEntity::COLUMN_IP = "IP";
const String DevicesEntity::COLUMN_NAME = "Name";
const String DevicesEntity::COLUMN_PARENTCHIPID = "ParentChipId";
const String DevicesEntity::COLUMN_APSSID = "ApSSID";
const String DevicesEntity::COLUMN_APPASSWORD = "ApPassword";


#endif // DEVICESENTITY_H