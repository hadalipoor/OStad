#ifndef PHOTORESISTORENTITY_H
#define PHOTORESISTORENTITY_H

#include "..\Entity.h"

class PhotoresistorEntity : public Entity {
public:
    static const String COLUMN_LOW_TRESHOLD;
    static const String COLUMN_HIGH_TRESHOLD;

private:
    int lowTreshold;
    int highTreshold;

public:
    PhotoresistorEntity() : Entity(), lowTreshold(0), highTreshold(0) {}

    PhotoresistorEntity(int id, int lowTreshold, int highTreshold) : Entity() {
        this->id = id;
        this->lowTreshold = lowTreshold;
        this->highTreshold = highTreshold;
        SetValue(COLUMN_LOW_TRESHOLD, String(this->lowTreshold));
        SetValue(COLUMN_HIGH_TRESHOLD, String(this->highTreshold));
    }

    PhotoresistorEntity(int lowTreshold, int highTreshold) : 
        PhotoresistorEntity(0, lowTreshold, highTreshold) {}

    static PhotoresistorEntity fromEntity(Entity entity) {
        PhotoresistorEntity photoresistorEntity = PhotoresistorEntity();
        photoresistorEntity.fromString(entity.toString());
        return photoresistorEntity;
    }

    // Getters
    int getLowTreshold() {
        lowTreshold = GetValue(COLUMN_LOW_TRESHOLD).toInt();
        return lowTreshold;
    }

    int getHighTreshold() {
        highTreshold = GetValue(COLUMN_HIGH_TRESHOLD).toInt();
        return highTreshold;
    }

    // Setters
    void setLowTreshold(int value) {
        lowTreshold = value;
        SetValue(COLUMN_LOW_TRESHOLD, String(lowTreshold));
    }

    void setHighTreshold(int value) {
        highTreshold = value;
        SetValue(COLUMN_HIGH_TRESHOLD, String(highTreshold));
    }

};

const String PhotoresistorEntity::COLUMN_LOW_TRESHOLD = "LowTreshold";
const String PhotoresistorEntity::COLUMN_HIGH_TRESHOLD = "HighTreshold";

#endif // PHOTORESISTORENTITY_H
