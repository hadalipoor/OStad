#ifndef ICLOCK_H
#define ICLOCK_H

#include "RTClib.h"
#include "JalaliDateTime.h"
#include "EBPDateTime.h"
#include <time.h>

class IClock {
public:
    virtual ~IClock() {}

    virtual EBPDateTime now() = 0;
    virtual JalaliDateTime nowJalali() = 0;
    virtual void adjust(const EBPDateTime& dt) = 0;
    virtual void syncTimeWithServer() = 0;
    virtual void initialize() = 0;
};

#endif
