#ifndef DEVICESENTITY_H
#define DEVICESENTITY_H

#include "..\Entity.h"

enum class DevicesType {Server, Client};

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
    String DeviceType;
    String ChipId;
    String IP;
    String Name;
    String ParentChipId;
    String ApSSID;
    String ApPassword;

public:
    DevicesEntity() : Entity() {}

    DevicesEntity(int id, String _DeviceType, String _ChipId, String _IP, String _Name, String _ParentChipId, String _ApSSID, String _ApPassword) : Entity(id) {
        DeviceType = _DeviceType;
        ChipId = _ChipId;
        IP = _IP;
        Name = _Name;
        ParentChipId = _ParentChipId;
        ApSSID = _ApSSID;
        ApPassword = _ApPassword;
    }

    DevicesEntity(String _DeviceType, String _ChipId, String _IP, String _Name, String _ParentChipId, String _ApSSID, String _ApPassword):
    DevicesEntity(0, _DeviceType, _ChipId, _IP, _Name, _ParentChipId, _ApSSID, _ApPassword)
    {

    }
    
    DevicesEntity(DevicesType _DeviceType, String _ChipId, String _IP, String _Name, String _ParentChipId, String _ApSSID, String _ApPassword):
    DevicesEntity(0, getDeviceType(_DeviceType), _ChipId, _IP, _Name, _ParentChipId, _ApSSID, _ApPassword)
    {

    }


    // Getters
    String getDeviceType() {
        DeviceType = GetValue(COLUMN_DEVICETYPE);
        return DeviceType;
    }
    String getChipId() {
        ChipId = GetValue(COLUMN_CHIPID);
        return ChipId;
    }
    String getIP() {
        IP = GetValue(COLUMN_IP);
        return IP;
    }
    String getName() {
        Name = GetValue(COLUMN_NAME);
        return Name;
    }
    String getParentChipId() {
        ParentChipId = GetValue(COLUMN_PARENTCHIPID);
        return ParentChipId;
    }
    String getApSSID() {
        ApSSID = GetValue(COLUMN_APSSID);
        return ApSSID;
    }
    String getApPassword() {
        ApPassword = GetValue(COLUMN_APPASSWORD);
        return ApPassword;
    }

    // Setters
    void setDeviceType(const String &_DeviceType) {
        DeviceType = _DeviceType;
        SetValue(COLUMN_DEVICETYPE, DeviceType);
    }
    void setChipId(const String &_ChipId) {
        ChipId = _ChipId;
        SetValue(COLUMN_CHIPID, ChipId);
    }
    void setIP(const String &_IP) {
        IP = _IP;
        SetValue(COLUMN_IP, IP);
    }
    void setName(const String &_Name) {
        Name = _Name;
        SetValue(COLUMN_NAME, Name);
    }
    void setParentChipId(const String &_ParentChipId) {
        ParentChipId = _ParentChipId;
        SetValue(COLUMN_PARENTCHIPID, ParentChipId);
    }
    void setApSSID(const String &_ApSSID) {
        ApSSID = _ApSSID;
        SetValue(COLUMN_APSSID, ApSSID);
    }
    void setApPassword(const String &_ApPassword) {
        ApPassword = _ApPassword;
        SetValue(COLUMN_APPASSWORD, ApPassword);
    }

    String getDeviceType(DevicesType _devicesType)
    {
        if (_devicesType == DevicesType::Client)
        {
            return "Client";
        }
        else
        {
            return "Server";
        }        
    }

    static DevicesEntity fromEntity(Entity entity)
    {
        DevicesEntity devicesEntity = DevicesEntity();
        devicesEntity.fromString(entity.toString());
        return devicesEntity;
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