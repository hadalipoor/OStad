#define OSTAD_NETWORK_DISABLE
#define OSTAD_MODULES_DISABLE
#ifndef LIGHTSCHEDULEENTITY_H
#define LIGHTSCHEDULEENTITY_H

#include <OStad.h>

class LightScheduleEntity : public Entity {
public:
    static const String COLUMN_TITLE;
    static const String COLUMN_RELAYID;
    static const String COLUMN_RELAYSTATUS;
    static const String COLUMN_ACTIONTIME;

    String Title;
    int RelayId;
    bool RelayStatus;
    EBPDateTime ActionTime;

    // Constructors
    LightScheduleEntity() : Entity() {}
    LightScheduleEntity(int id, String _Title, int _RelayId, bool _RelayStatus, EBPDateTime _ActionTime) : Entity() {
        this->id = id;
        setTitle(_Title);
        setRelayId(_RelayId);
        setRelayStatus(_RelayStatus);
        setActionTime(_ActionTime);
        
        addColumn(COLUMN_TITLE, String(Title), "String");
        addColumn(COLUMN_RELAYID, String(RelayId), "int");
        addColumn(COLUMN_RELAYSTATUS, String(RelayStatus), "bool");
        addColumn(COLUMN_ACTIONTIME, ActionTime.toDateTimeString(), "EBPDateTime");
    }
    LightScheduleEntity(String _Title, int _RelayId, bool _RelayStatus, EBPDateTime _ActionTime) : 
        LightScheduleEntity(0, _Title, _RelayId, _RelayStatus, _ActionTime) {}

    // Setters
    void setTitle(const String& title) {
        Title = title;
        SetValue(LightScheduleEntity::COLUMN_TITLE, title);
    }
    void setRelayId(int relayId) {
        RelayId = relayId;
        SetValue(LightScheduleEntity::COLUMN_RELAYID, String(relayId));
    }
    void setRelayStatus(bool relayStatus) {
        RelayStatus = relayStatus;
        SetValue(LightScheduleEntity::COLUMN_RELAYSTATUS, String(relayStatus));
    }
    void setActionTime(EBPDateTime actionTime) {
        ActionTime = actionTime;
        SetValue(LightScheduleEntity::COLUMN_ACTIONTIME, actionTime.toDateTimeString());
    }

    // Getters
    String getTitle() {
        return GetValue(LightScheduleEntity::COLUMN_TITLE);
    }
    int getRelayId() {
        return GetValue(LightScheduleEntity::COLUMN_RELAYID).toInt();
    }
    bool getRelayStatus() {
        return GetValue(LightScheduleEntity::COLUMN_RELAYSTATUS).toInt();
    }
    EBPDateTime getActionTime() {
        return EBPDateTime(GetValue(LightScheduleEntity::COLUMN_ACTIONTIME));
    }

    // Conversion from base Entity class
    static LightScheduleEntity fromEntity(Entity entity)
    {
        LightScheduleEntity lightscheduleentity = LightScheduleEntity();
        lightscheduleentity.fromString(entity.toString());
        return lightscheduleentity;
    }
};

// Static members initialization
const String LightScheduleEntity::COLUMN_TITLE = "Title";
const String LightScheduleEntity::COLUMN_RELAYID = "RelayId";
const String LightScheduleEntity::COLUMN_RELAYSTATUS = "RelayStatus";
const String LightScheduleEntity::COLUMN_ACTIONTIME = "ActionTime";

#endif // LIGHTSCHEDULEENTITY_H
