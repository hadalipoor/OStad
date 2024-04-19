#ifndef CLOCK_H
#define CLOCK_H

#include <WiFi.h>
#include "time.h"

#include "JalaliDateTime.h"
#include "IClock.h"
#include "InternalClock.h"
#include "../Config/System/SystemConfigKeys.h"
#include "../Logging/LogTitles.h"
#include "../Context.h"

enum class ClockType { DS3231, DS1307, Internal };

class Clock : public IClock {
private:
    RTC_DS3231 ds3231;
    RTC_DS1307 ds1307;
    ClockType clockType;
    Context* context;
    bool _isinitialized;
    bool _isSynced;
    InternalClock internalClock;

public:
    Clock(Context* context) : context(context), _isinitialized(false), _isSynced(false) {
        
    }

    void initialize() override {
        String clockTypeStr = "Internal"; // Replace with dynamic config if needed
        clockTypeStr = context->getConfig()->getSystemConfig()->get(SystemConfigKey::CLOCK_TYPE);
        // Initialize the correct clock based on the type
        if (clockTypeStr == "DS3231") {
            if (!ds3231.begin()) {
                Serial.println("DS3231 Clock not Started.");
                return;
            }
            
            Serial.println("DS3231 Clock Started Succesfully.");
            clockType = ClockType::DS3231;
        }
        else if(clockTypeStr == "DS1307"){
            if (!ds1307.begin()) {
                context->getErrorHandler()->handleError(ErrorType::CustomError, "DS1307 initialization failed");
                return;
            }
            clockType = ClockType::DS1307;
        }
        else if(clockTypeStr == "Internal"){
            clockType = ClockType::Internal;
        }
        _isinitialized = true;
    }

    EBPDateTime now() override {
        if (!_isinitialized) {
            return EBPDateTime(2000,1,1,0,0,0);
        }
        
        switch (clockType) {
        case ClockType::DS3231:
            return EBPDateTime(ds3231.now());
        case ClockType::DS1307:
            return EBPDateTime(ds1307.now());
        case ClockType::Internal:
            if(!_isSynced) return EBPDateTime(2000,1,1,0,0,0);
            return EBPDateTime(internalClock.now());
        }
    }

    JalaliDateTime nowJalali() override {
        // Return the current date and time based on the clock type in Jalali Calendar
        if (!_isinitialized)
        {
            return JalaliDateTime(DateTime(2000,1,1,0,0,0));
        }
        JalaliDateTime jalaliDateTime = JalaliDateTime();
        switch (clockType) {
        case ClockType::DS3231:
            jalaliDateTime.ConvertToJalali(ds3231.now());
            return jalaliDateTime;
        case ClockType::DS1307:
            jalaliDateTime.ConvertToJalali(ds1307.now());
            return jalaliDateTime;
        }
    }

    void adjust(const EBPDateTime& dt) override {
        // Set the current date and time based on the clock type
        
        switch (clockType) {
        case ClockType::DS3231:
            ds3231.adjust(dt);
            break;
        case ClockType::DS1307:
            ds1307.adjust(dt);
            break;
        }
    }

    void syncTimeWithServer() override {
        if (context->getConfig()->getSystemConfig()->get(SystemConfigKey::SYNC_CLOCK) == "false")
        {
            return;
        }
        
        context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_CLOCK, "Clock is Syncing with NTP ...");
        if(clockType == ClockType::Internal){
            if(internalClock.synchronize_ntp()) _isSynced = true;
        } else {

            configTime(0, 0, "pool.ntp.org"); // UTC

            time_t now = 0;
            struct tm timeinfo = {0};
            int retry = 0;
            const int retry_count = 10;
            while(timeinfo.tm_year < (2016 - 2000) && ++retry < retry_count) {
                delay(1000);
                time(&now);
                localtime_r(&now, &timeinfo);
            }

            if (retry < retry_count) {
                DateTime dt(timeinfo.tm_year + 2000, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
                adjust(dt);
                context->getLogger()->log(LogLevel::INFO_LEVEL, "Time Sync", "Time synchronized with NTP server");
            } else {
                context->getErrorHandler()->handleError(ErrorType::CustomError, "Failed to get time from NTP server");
            }
        }
        context->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::SYSTEM_CLOCK, "Clock Synced with NTP.");

    }
};

#endif
