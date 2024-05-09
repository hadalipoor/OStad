#ifndef SECURITYQUESTIONENTITY_H
#define SECURITYQUESTIONENTITY_H

#include "../Entity.h"

class SecurityQuestionEntity : public Entity {
public:
    static const String COLUMN_USERID;
    static const String COLUMN_SECURITYQUESTIONTITLEID;
    static const String COLUMN_ANSWER;

private:
    int userId;
    String securityQuestionTitleId;
    String answer;

public:
    SecurityQuestionEntity() : Entity(), userId(0), securityQuestionTitleId(""), answer("") {}

    SecurityQuestionEntity(int id, int _UserId, String _SecurityQuestionTitleId, String _Answer) : Entity() {
        this->id = id;
        this->userId = _UserId;
        this->securityQuestionTitleId = _SecurityQuestionTitleId;
        this->answer = _Answer;
        SetValue(COLUMN_USERID, String(this->userId));
        SetValue(COLUMN_SECURITYQUESTIONTITLEID, this->securityQuestionTitleId);
        SetValue(COLUMN_ANSWER, this->answer);
    }

    SecurityQuestionEntity(int _UserId, String _SecurityQuestionTitleId, String _Answer) : 
        SecurityQuestionEntity(0, _UserId, _SecurityQuestionTitleId, _Answer) {}

    static SecurityQuestionEntity fromEntity(Entity entity) {
        SecurityQuestionEntity securityquestionentity = SecurityQuestionEntity();
        securityquestionentity.fromString(entity.toString());
        return securityquestionentity;
    }

    // Getters
    int getUserId() {
        userId = GetValue(COLUMN_USERID).toInt();
        return userId;
    }

    String getSecurityQuestionTitleId() {
        securityQuestionTitleId = GetValue(COLUMN_SECURITYQUESTIONTITLEID);
        return securityQuestionTitleId;
    }

    String getAnswer() {
        answer = GetValue(COLUMN_ANSWER);
        return answer;
    }

    // Setters
    void setUserId(int value) {
        userId = value;
        SetValue(COLUMN_USERID, String(userId));
    }

    void setSecurityQuestionTitleId(String value) {
        securityQuestionTitleId = value;
        SetValue(COLUMN_SECURITYQUESTIONTITLEID, securityQuestionTitleId);
    }

    void setAnswer(String value) {
        answer = value;
        SetValue(COLUMN_ANSWER, answer);
    }
};

const String SecurityQuestionEntity::COLUMN_USERID = "UserId";
const String SecurityQuestionEntity::COLUMN_SECURITYQUESTIONTITLEID = "SecurityQuestionTitleId";
const String SecurityQuestionEntity::COLUMN_ANSWER = "Answer";

#endif // SECURITYQUESTIONENTITY_H
