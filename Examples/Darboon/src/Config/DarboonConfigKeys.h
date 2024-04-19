
#ifndef DARBOONCONFIGKEYS_H
#define DARBOONCONFIGKEYS_H

class DarboonConfigKey
{
private:

public:
    static const String SYSTEM_ENABLE;
    static const String RFID_ENABLE;
    static const String WIFI_OPEN_DOOR;
};

const String DarboonConfigKey::SYSTEM_ENABLE = "system_enable";
const String DarboonConfigKey::RFID_ENABLE = "rfid_enable";
const String DarboonConfigKey::WIFI_OPEN_DOOR = "wifi_open_door";

#endif // DARBOONCONFIGKEYS_H
