
#ifndef GROWIFYCONFIGKEYS_H
#define GROWIFYCONFIGKEYS_H

class GrowifyConfigKey
{
private:

public:
    static const String SYSTEM_ENABLE;
    static const String POLLING_INTERVAL;
    static const String DATA_AGGREGATION_INTERVAL;
    static const String ALERT_THRESHOLD_TEMPERATURE;
    static const String ALERT_THRESHOLD_HUMIDITY;
    static const String ALERT_THRESHOLD_LIGHT;
    static const String ALERT_THRESHOLD_SOIL_MOISTURE;
    static const String SMS_ALERTS_ENABLE;
    static const String SMS_MESSAGE_TEMPERATURE;
    static const String SMS_MESSAGE_HUMIDITY;
    static const String SMS_MESSAGE_LIGHT;
    static const String SMS_MESSAGE_SOIL_MOISTURE;
    static const String SMS_ALERTS_NUMBER;
    static const String DATABASE_SIZE_LIMIT;
    static const String AUTOMATIC_UPDATES_ENABLE;
    static const String AUTOMATIC_UPDATES_INTERVAL;
    static const String AUTOMATIC_CONDITION_ADJUSTMENTS_ENABLE;
};

const String GrowifyConfigKey::SYSTEM_ENABLE = "system_enable";
const String GrowifyConfigKey::POLLING_INTERVAL = "polling_interval";
const String GrowifyConfigKey::DATA_AGGREGATION_INTERVAL = "data_aggregation_interval";
const String GrowifyConfigKey::ALERT_THRESHOLD_TEMPERATURE = "alert_threshold_temperature";
const String GrowifyConfigKey::ALERT_THRESHOLD_HUMIDITY = "alert_threshold_humidity";
const String GrowifyConfigKey::ALERT_THRESHOLD_LIGHT = "alert_threshold_light";
const String GrowifyConfigKey::ALERT_THRESHOLD_SOIL_MOISTURE = "alert_threshold_soil_moisture";
const String GrowifyConfigKey::SMS_ALERTS_ENABLE = "SMS_alerts_enable";
const String GrowifyConfigKey::SMS_MESSAGE_TEMPERATURE = "SMS_message_temperature";
const String GrowifyConfigKey::SMS_MESSAGE_HUMIDITY = "SMS_message_humidity";
const String GrowifyConfigKey::SMS_MESSAGE_LIGHT = "SMS_message_light";
const String GrowifyConfigKey::SMS_MESSAGE_SOIL_MOISTURE = "SMS_message_soil_moisture";
const String GrowifyConfigKey::SMS_ALERTS_NUMBER = "SMS_alerts_number";
const String GrowifyConfigKey::DATABASE_SIZE_LIMIT = "database_size_limit";
const String GrowifyConfigKey::AUTOMATIC_UPDATES_ENABLE = "automatic_updates_enable";
const String GrowifyConfigKey::AUTOMATIC_UPDATES_INTERVAL = "automatic_updates_interval";
const String GrowifyConfigKey::AUTOMATIC_CONDITION_ADJUSTMENTS_ENABLE = "automatic_condition_adjustments_enable";

#endif // GROWIFYCONFIGKEYS_H
