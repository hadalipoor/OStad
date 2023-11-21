#ifndef ACCOUNTACTIVITYLOGENTITY_H
#define ACCOUNTACTIVITYLOGENTITY_H

#include "../Entity.h"

class AccountActivityLogEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_ACTIVITY;
    static const String COLUMN_TIMESTAMP;
    

    int UserId;
    String Activity;
    EBPDateTime Timestamp;
    

    AccountActivityLogEntity()  : Entity(){}

    AccountActivityLogEntity(int id, int _UserId, String _Activity, EBPDateTime _Timestamp) : Entity() {
        this->id = id;
        UserId = _UserId;
        Activity = _Activity;
        Timestamp = _Timestamp;
        

        addColumn(COLUMN_USERID, String(UserId), "int");
        addColumn(COLUMN_ACTIVITY, String(Activity), "String");
        addColumn(COLUMN_TIMESTAMP, Timestamp.toDateTimeString(), "EBPDateTime");
        
    }

    AccountActivityLogEntity(int _UserId, String _Activity, EBPDateTime _Timestamp) : 
        AccountActivityLogEntity(0, _UserId, _Activity, _Timestamp)  {}

    static AccountActivityLogEntity fromEntity(Entity entity)
    {
        AccountActivityLogEntity accountactivitylogentity = AccountActivityLogEntity();
        accountactivitylogentity.fromString(entity.toString());
        return accountactivitylogentity;
    }

    // Setters and Getters for each field
};

const String AccountActivityLogEntity::COLUMN_USERID = "UserId";
const String AccountActivityLogEntity::COLUMN_ACTIVITY = "Activity";
const String AccountActivityLogEntity::COLUMN_TIMESTAMP = "Timestamp";


#endif // ACCOUNTACTIVITYLOGENTITY_H