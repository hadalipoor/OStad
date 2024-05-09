#ifndef ACCOUNTACTIVITYLOGENTITY_H
#define ACCOUNTACTIVITYLOGENTITY_H

#include "../Entity.h"

class AccountActivityLogEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_ACTIVITY;
    static const String COLUMN_TIMESTAMP;

private:
    int userId;
    String activity;
    EBPDateTime timestamp;

public:
    AccountActivityLogEntity() : Entity(), userId(0), activity(""), timestamp(EBPDateTime()) {}

    AccountActivityLogEntity(int id, int _UserId, String _Activity, EBPDateTime _Timestamp) : Entity() {
        this->id = id;
        this->userId = _UserId;
        this->activity = _Activity;
        this->timestamp = _Timestamp;
        SetValue(COLUMN_USERID, String(this->userId));
        SetValue(COLUMN_ACTIVITY, this->activity);
        SetValue(COLUMN_TIMESTAMP, this->timestamp.toDateTimeString());
    }

    AccountActivityLogEntity(int _UserId, String _Activity, EBPDateTime _Timestamp) : 
        AccountActivityLogEntity(0, _UserId, _Activity, _Timestamp)  {}

    static AccountActivityLogEntity fromEntity(Entity entity) {
        AccountActivityLogEntity accountactivitylogentity = AccountActivityLogEntity();
        accountactivitylogentity.fromString(entity.toString());
        return accountactivitylogentity;
    }

    // Getters
    int getUserId() {
        userId = GetValue(COLUMN_USERID).toInt();
        return userId;
    }

    String getActivity() {
        activity = GetValue(COLUMN_ACTIVITY);
        return activity;
    }

    EBPDateTime getTimestamp() {
        timestamp.fromString(GetValue(COLUMN_TIMESTAMP));
        return timestamp;
    }

    // Setters
    void setUserId(int value) {
        userId = value;
        SetValue(COLUMN_USERID, String(userId));
    }

    void setActivity(String value) {
        activity = value;
        SetValue(COLUMN_ACTIVITY, activity);
    }

    void setTimestamp(EBPDateTime value) {
        timestamp = value;
        SetValue(COLUMN_TIMESTAMP, timestamp.toDateTimeString());
    }
};

const String AccountActivityLogEntity::COLUMN_USERID = "UserId";
const String AccountActivityLogEntity::COLUMN_ACTIVITY = "Activity";
const String AccountActivityLogEntity::COLUMN_TIMESTAMP = "Timestamp";

#endif // ACCOUNTACTIVITYLOGENTITY_H
