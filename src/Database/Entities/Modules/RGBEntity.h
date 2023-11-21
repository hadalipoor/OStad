#ifndef RGBENTITY_H
#define RGBENTITY_H

#include "..\Entity.h"

class RGBEntity : public Entity {
public:
    static const String COLUMN_TYPE;
    static const String COLUMN_RPIN;
    static const String COLUMN_GPIN;
    static const String COLUMN_BPIN;

    String Type;
    int Rpin;
    int Gpin;
    int Bpin;

    RGBEntity() : Entity() {}

    RGBEntity(int id, const String &_Type, int rpin, int gpin, int bpin) : Entity() {
        this->id = id;
        Type = _Type;
        Rpin = rpin;
        Gpin = gpin;
        Bpin = bpin;
        addColumn(COLUMN_TYPE, Type, "string");
        addColumn(COLUMN_RPIN, String(Rpin), "int");
        addColumn(COLUMN_GPIN, String(Gpin), "int");
        addColumn(COLUMN_BPIN, String(Bpin), "int");
    }

    RGBEntity(const String &_Type, int rpin, int gpin, int bpin) : 
        RGBEntity(0, _Type, rpin, gpin, bpin) {}

    static RGBEntity fromEntity(Entity entity)
    {
        RGBEntity rgbEntity = RGBEntity();
        rgbEntity.fromString(entity.toString());
        return rgbEntity;
    }

    // Setters and Getters for each field
};

const String RGBEntity::COLUMN_TYPE = "Type";
const String RGBEntity::COLUMN_RPIN = "Rpin";
const String RGBEntity::COLUMN_GPIN = "Gpin";
const String RGBEntity::COLUMN_BPIN = "Bpin";

#endif // RGBENTITY_H
