#ifndef LIGHTSCHEDULECONTROLLER_H
#define LIGHTSCHEDULECONTROLLER_H

#include "LightScheduleEntity.h"
#include <OStad.h>

class LightScheduleController : public MainController<LightScheduleEntity> {
public:
    Context* context;
    LightScheduleController(Context* context, StorageType _storageType) : MainController<LightScheduleEntity>(context, "lightschedule", _storageType), context(context) {}

    bool IsTimeToActive(int id) {
        LightScheduleEntity lightScheduleEntity = GetById(id);
        return lightScheduleEntity.getActionTime().isInSameTime(context->getClock()->now());
    }

    std::vector<LightScheduleEntity> GetActiveHighRelaySchedule() {
        return Get(LightScheduleEntity::COLUMN_RELAYSTATUS + String("=" + 1));
    }

};

#endif // LIGHTSCHEDULECONTROLLER_H
