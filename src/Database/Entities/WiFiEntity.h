#ifndef WIFIENTITY_H
#define WIFIENTITY_H

#include "Entity.h"

class WiFiEntity : public Entity {
public:
    static const String COLUMN_SSID;
    static const String COLUMN_PASSWORD;

    String SSID;
    String Password;

    WiFiEntity() : Entity() {}

    WiFiEntity(int id, const String &_SSID, const String &_Password) : Entity() {
        this->id = id;
        SSID = _SSID;
        Password = _Password;
        addColumn(COLUMN_SSID, SSID, "string");
        addColumn(COLUMN_PASSWORD, Password, "string");
    }

    WiFiEntity(const String &_SSID, const String &_Password) : WiFiEntity(0, _SSID, _Password) {}

    static WiFiEntity fromEntity(Entity entity)
    {
        WiFiEntity wifiEntity = WiFiEntity();
        wifiEntity.fromString(entity.toString());
        return wifiEntity;
    }

    void setSSID(const String &_SSID) {
        SSID = _SSID;
        SetValue(COLUMN_SSID, _SSID);
    }

    String getSSID() {
        return GetValue(COLUMN_SSID);
    }

    void setPassword(const String &_Password) {
        Password = _Password;
        SetValue(COLUMN_PASSWORD, _Password);
    }

    String getPassword() {
        return GetValue(COLUMN_PASSWORD);
    }
};

const String WiFiEntity::COLUMN_SSID = "SSID";
const String WiFiEntity::COLUMN_PASSWORD = "Password";

#endif // WIFIENTITY_H
