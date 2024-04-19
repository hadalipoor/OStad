#ifndef SECURITYQUESTIONTITLEENTITY_H
#define SECURITYQUESTIONTITLEENTITY_H

#include <OStad.h>

class SecurityQuestionTitleEntity : public Entity {
public:
    static const String COLUMN_QUESTIONTITLE;
    

    String QuestionTitle;
    

    SecurityQuestionTitleEntity()  : Entity(){}

    SecurityQuestionTitleEntity(int id, String _QuestionTitle) : Entity() {
        this->id = id;
        QuestionTitle = _QuestionTitle;
        

        addColumn(COLUMN_QUESTIONTITLE, String(QuestionTitle), "String");
        
    }

    SecurityQuestionTitleEntity(String _QuestionTitle) : 
        SecurityQuestionTitleEntity(0, _QuestionTitle)  {}

    static SecurityQuestionTitleEntity fromEntity(Entity entity)
    {
        SecurityQuestionTitleEntity securityquestiontitleentity = SecurityQuestionTitleEntity();
        securityquestiontitleentity.fromString(entity.toString());
        return securityquestiontitleentity;
    }

    // Setters and Getters for each field
};

const String SecurityQuestionTitleEntity::COLUMN_QUESTIONTITLE = "QuestionTitle";


#endif // SECURITYQUESTIONTITLEENTITY_H