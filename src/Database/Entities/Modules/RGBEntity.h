#ifndef RGBENTITY_H
#define RGBENTITY_H

#include "..\Entity.h"

class RGBEntity : public Entity {
public:
    static const String COLUMN_TYPE;
    static const String COLUMN_RPIN;
    static const String COLUMN_GPIN;
    static const String COLUMN_BPIN;

private:
    String type;
    int rPin;
    int gPin;
    int bPin;

public:
    RGBEntity() : Entity(), type(""), rPin(0), gPin(0), bPin(0) {}

    RGBEntity(int id, const String &_Type, int rPin, int gPin, int bPin) : Entity() {
        this->id = id;
        this->type = _Type;
        this->rPin = rPin;
        this->gPin = gPin;
        this->bPin = bPin;
        SetValue(COLUMN_TYPE, this->type);
        SetValue(COLUMN_RPIN, String(this->rPin));
        SetValue(COLUMN_GPIN, String(this->gPin));
        SetValue(COLUMN_BPIN, String(this->bPin));
    }

    RGBEntity(const String &_Type, int rPin, int gPin, int bPin) : 
        RGBEntity(0, _Type, rPin, gPin, bPin) {}

    static RGBEntity fromEntity(Entity entity) {
        RGBEntity rgbEntity = RGBEntity();
        rgbEntity.fromString(entity.toString());
        return rgbEntity;
    }

    // Getters
    String getType() {
        type = GetValue(COLUMN_TYPE);
        return type;
    }

    int getRPin() {
        rPin = GetValue(COLUMN_RPIN).toInt();
        return rPin;
    }

    int getGPin() {
        gPin = GetValue(COLUMN_GPIN).toInt();
        return gPin;
    }

    int getBPin() {
        bPin = GetValue(COLUMN_BPIN).toInt();
        return bPin;
    }

    // Setters
    void setType(const String &value) {
        type = value;
        SetValue(COLUMN_TYPE, type);
    }

    void setRPin(int value) {
        rPin = value;
        SetValue(COLUMN_RPIN, String(rPin));
    }

    void setGPin(int value) {
        gPin = value;
        SetValue(COLUMN_GPIN, String(gPin));
    }

    void setBPin(int value) {
        bPin = value;
        SetValue(COLUMN_BPIN, String(bPin));
    }

};

const String RGBEntity::COLUMN_TYPE = "Type";
const String RGBEntity::COLUMN_RPIN = "Rpin";
const String RGBEntity::COLUMN_GPIN = "Gpin";
const String RGBEntity::COLUMN_BPIN = "Bpin";

#endif // RGBENTITY_H
