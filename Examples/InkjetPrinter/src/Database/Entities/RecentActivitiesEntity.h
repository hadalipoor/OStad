#ifndef RECENTACTIVITIESENTITY_H
#define RECENTACTIVITIESENTITY_H

#include <OStad.h>

class RecentActivitiesEntity : public Entity {
public:
    static const String COLUMN_TITLE;
    

    String Title;
    

    RecentActivitiesEntity()  : Entity(){}

    RecentActivitiesEntity(int id, String _Title) : Entity() {
        this->id = id;
        Title = _Title;
        

        addColumn(COLUMN_TITLE, String(Title), "String");
        
    }

    RecentActivitiesEntity(String _Title) : 
        RecentActivitiesEntity(0, _Title)  {}

    static RecentActivitiesEntity fromEntity(Entity entity)
    {
        RecentActivitiesEntity recentactivitiesentity = RecentActivitiesEntity();
        recentactivitiesentity.fromString(entity.toString());
        return recentactivitiesentity;
    }

    // Setters and Getters for each field
};

const String RecentActivitiesEntity::COLUMN_TITLE = "Title";


#endif // RECENTACTIVITIESENTITY_H