#ifndef SABOORATANKER_H
#define SABOORATANKER_H

#include "ISabooraTanker.h"
#include "../AppContext.h"
#include "../Config/DefaultSabooraTankerConfigs.h"

class SabooraTanker : public ISabooraTanker {
private:
    AppContext* context;

public:
    SabooraTanker(AppContext* context);
    
    void initialize() override;
    void update() override;
};

SabooraTanker::SabooraTanker(AppContext* context)
    : context(context) {}

void SabooraTanker::initialize() {

}

void SabooraTanker::update() {

}

#endif //SABOORATANKER_H
