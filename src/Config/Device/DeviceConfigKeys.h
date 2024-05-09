
#ifndef DEVICECONFIGKEYS_H
#define DEVICECONFIGKEYS_H

class DeviceConfigKeys
{
private:

public:
    static const String DEVICE_TYPE;
    static const String CHIP_ID;
    static const String DEVICE_NAME;
    static const String PROTOCOL_TYPE;
};

const String DeviceConfigKeys::DEVICE_TYPE = "device_type";
const String DeviceConfigKeys::CHIP_ID = "chip_id";
const String DeviceConfigKeys::DEVICE_NAME = "device_name";
const String DeviceConfigKeys::PROTOCOL_TYPE = "Protocol_type";

#endif // DEVICETESTCONFIGKEYS_H
