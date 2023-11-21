#ifndef SECURITYQUESTIONENTITY_H
#define SECURITYQUESTIONENTITY_H

#include "../Entity.h"

class SecurityQuestionEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_SECURITYQUESTIONTITLEID;
    static const String COLUMN_ANSWER;
    

    int UserId;
    String SecurityQuestionTitleId;
    String Answer;
    

    SecurityQuestionEntity()  : Entity(){}

    SecurityQuestionEntity(int id, int _UserId, String _SecurityQuestionTitleId, String _Answer) : Entity() {
        this->id = id;
        UserId = _UserId;
        SecurityQuestionTitleId = _SecurityQuestionTitleId;
        Answer = _Answer;
        

        addColumn(COLUMN_USERID, String(UserId), "int");
        addColumn(COLUMN_SECURITYQUESTIONTITLEID, String(SecurityQuestionTitleId), "String");
        addColumn(COLUMN_ANSWER, String(Answer), "String");
        
    }

    SecurityQuestionEntity(int _UserId, String _SecurityQuestionTitleId, String _Answer) : 
        SecurityQuestionEntity(0, _UserId, _SecurityQuestionTitleId, _Answer)  {}

    static SecurityQuestionEntity fromEntity(Entity entity)
    {
        SecurityQuestionEntity securityquestionentity = SecurityQuestionEntity();
        securityquestionentity.fromString(entity.toString());
        return securityquestionentity;
    }

    // Setters and Getters for each field
};

const String SecurityQuestionEntity::COLUMN_USERID = "UserId";
const String SecurityQuestionEntity::COLUMN_SECURITYQUESTIONTITLEID = "SecurityQuestionTitleId";
const String SecurityQuestionEntity::COLUMN_ANSWER = "Answer";


#endif // SECURITYQUESTIONENTITY_H