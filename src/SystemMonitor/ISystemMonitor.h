#ifndef ISYSTEM_MONITOR_H
#define ISYSTEM_MONITOR_H

#include "Esp.h"
#include "LittleFS.h"
#include "SD.h"
#include "ArduinoJson.h"

struct StorageInfo {
    size_t totalBytes;
    size_t usedBytes;
};

class ISystemMonitor {
public:
    virtual ~ISystemMonitor() {}

    // CPU info
    virtual uint8_t getChipCores() = 0;
    virtual uint8_t getChipRevision() = 0;
    virtual const char* getChipModel() = 0;
    virtual const char* getSdkVersion() = 0;
    virtual uint32_t getFlashChipSize() = 0;
    virtual uint32_t getFlashChipSpeed() = 0;
    virtual FlashMode_t getFlashChipMode() = 0;
    virtual uint64_t getEfuseMac() = 0;

    // RAM info
    virtual uint32_t getHeapSize() = 0;
    virtual uint32_t getFreeHeap() = 0;
    virtual uint32_t getMinFreeHeap() = 0;
    virtual uint32_t getMaxAllocHeap() = 0;

    // SPIRAM info
    virtual uint32_t getPsramSize() = 0;
    virtual uint32_t getFreePsram() = 0;
    virtual uint32_t getMinFreePsram() = 0;
    virtual uint32_t getMaxAllocPsram() = 0;

    // Sketch info
    virtual uint32_t getSketchSize() = 0;
    virtual uint32_t getFreeSketchSpace() = 0;
    virtual String getSketchMD5() = 0;

    // File system info
    virtual StorageInfo getLittleFSInfo() = 0;
    virtual StorageInfo getSDInfo() = 0;

    // Uptime info
    virtual unsigned long getUptime() = 0;

    virtual String getSystemMonitorJson() = 0;

};

#endif // ISYSTEM_MONITOR_H
