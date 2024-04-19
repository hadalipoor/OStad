#ifndef GUESTSCONTROLLER_H
#define GUESTSCONTROLLER_H

#include <OStad.h>
#include "../Entities/GuestsEntity.h"
#include "../../AppContext.h"

class GuestsController : public MainController<GuestsEntity> {
public:
    AppContext* appContext;
    GuestsController(AppContext* appContext, StorageType _storageType) : MainController<GuestsEntity>(appContext->systemContext ,"guests", _storageType), appContext(appContext) {}

    GuestsEntity getGuestByUid(String uid)
    {
        std::vector<GuestsEntity> guestEntities = Get(GuestsEntity::COLUMN_UID + String("=" + uid));
        if (guestEntities.size() > 0)
        {
            return guestEntities.at(0);
        }
        return GuestsEntity("","","",false, EBPDateTime(),EBPDateTime());        
    }

    GuestsEntity getWaitingGuest()
    {
        std::vector<GuestsEntity> guestEntities = Get(GuestsEntity::COLUMN_UID + String("=WAITING"));
        if (guestEntities.size() > 0)
        {
            return guestEntities.at(0);
        }
        return GuestsEntity("","","",false, EBPDateTime(),EBPDateTime());        
    }
};

#endif // GUESTSCONTROLLER_H