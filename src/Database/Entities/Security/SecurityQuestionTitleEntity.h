#ifndef SECURITYQUESTIONTITLEENTITY_H
#define SECURITYQUESTIONTITLEENTITY_H

#include "../Entity.h"

class SecurityQuestionTitleEntity : public Entity {
public:
    static const String COLUMN_QUESTIONTITLE;

private:
    String questionTitle;

public:
    SecurityQuestionTitleEntity() : Entity(), questionTitle("") {}

    SecurityQuestionTitleEntity(int id, String _QuestionTitle) : Entity() {
        this->id = id;
        this->questionTitle = _QuestionTitle;
        SetValue(COLUMN_QUESTIONTITLE, this->questionTitle);
    }

    SecurityQuestionTitleEntity(String _QuestionTitle) : 
        SecurityQuestionTitleEntity(0, _QuestionTitle) {}

    static SecurityQuestionTitleEntity fromEntity(Entity entity) {
        SecurityQuestionTitleEntity securityquestiontitleentity = SecurityQuestionTitleEntity();
        securityquestiontitleentity.fromString(entity.toString());
        return securityquestiontitleentity;
    }

    // Getters
    String getQuestionTitle() {
        questionTitle = GetValue(COLUMN_QUESTIONTITLE);
        return questionTitle;
    }

    // Setters
    void setQuestionTitle(String value) {
        questionTitle = value;
        SetValue(COLUMN_QUESTIONTITLE, questionTitle);
    }
};

const String SecurityQuestionTitleEntity::COLUMN_QUESTIONTITLE = "QuestionTitle";

#endif // SECURITYQUESTIONTITLEENTITY_H
