#ifndef PHOTORESISTORENTITY_H
#define PHOTORESISTORENTITY_H

#include "..\Entity.h"

class PhotoresistorEntity : public Entity {
public:
    static const String COLUMN_LOW_TRESHOLD;
    static const String COLUMN_HIGH_TRESHOLD;

    int LowTreshold;
    int HighTreshold;

    PhotoresistorEntity() : Entity() {}

    PhotoresistorEntity(int id, int lowTreshold, int highTreshold) : Entity() {
        this->id = id;
        LowTreshold = lowTreshold;
        HighTreshold = highTreshold;
        addColumn(COLUMN_LOW_TRESHOLD, String(LowTreshold), "int");
        addColumn(COLUMN_HIGH_TRESHOLD, String(HighTreshold), "int");
    }

    PhotoresistorEntity(int lowTreshold, int highTreshold) : 
        PhotoresistorEntity(0, lowTreshold, highTreshold) {}

    static PhotoresistorEntity fromEntity(Entity entity)
    {
        PhotoresistorEntity photoresistorEntity = PhotoresistorEntity();
        photoresistorEntity.fromString(entity.toString());
        return photoresistorEntity;
    }

    // Setters and Getters for each field
};

const String PhotoresistorEntity::COLUMN_LOW_TRESHOLD = "LowTreshold";
const String PhotoresistorEntity::COLUMN_HIGH_TRESHOLD = "HighTreshold";

#endif // PHOTORESISTORENTITY_H
