#ifndef RECENTACTIVITIESCONTROLLER_H
#define RECENTACTIVITIESCONTROLLER_H

#include <OStad.h>
#include "../Entities/RecentActivitiesEntity.h"
#include "../../AppContext.h"

class RecentActivitiesController : public MainController<RecentActivitiesEntity> {
public:
    AppContext* appContext;
    RecentActivitiesController(AppContext* appContext, StorageType _storageType) : MainController<RecentActivitiesEntity>(appContext->systemContext ,"recentactivities", _storageType), appContext(appContext) {}
};

#endif // RECENTACTIVITIESCONTROLLER_H