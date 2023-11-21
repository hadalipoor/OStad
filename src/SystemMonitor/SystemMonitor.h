#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include "ISystemMonitor.h"
#include "SD.h"

class SystemMonitor : public ISystemMonitor {
public:
    SystemMonitor();

    // CPU info
    virtual uint8_t getChipCores() override;
    virtual uint8_t getChipRevision() override;
    virtual const char* getChipModel() override;
    virtual const char* getSdkVersion() override;
    virtual uint32_t getFlashChipSize() override;
    virtual uint32_t getFlashChipSpeed() override;
    virtual FlashMode_t getFlashChipMode() override;
    virtual uint64_t getEfuseMac() override;

    // RAM info
    virtual uint32_t getHeapSize() override;
    virtual uint32_t getFreeHeap() override;
    virtual uint32_t getMinFreeHeap() override;
    virtual uint32_t getMaxAllocHeap() override;

    // SPIRAM info
    virtual uint32_t getPsramSize() override;
    virtual uint32_t getFreePsram() override;
    virtual uint32_t getMinFreePsram() override;
    virtual uint32_t getMaxAllocPsram() override;

    // Sketch info
    virtual uint32_t getSketchSize() override;
    virtual uint32_t getFreeSketchSpace() override;
    virtual String getSketchMD5() override;

    // File system info
    virtual StorageInfo getLittleFSInfo() override;
    virtual StorageInfo getSDInfo() override;

    // Uptime info
    virtual unsigned long getUptime() override;

    virtual String getSystemMonitorJson() override;


private:

};

SystemMonitor::SystemMonitor() {}

// CPU info
uint8_t SystemMonitor::getChipCores() {
    return ESP.getCpuFreqMHz();
}

uint8_t SystemMonitor::getChipRevision() {
    return ESP.getChipRevision();
}

const char* SystemMonitor::getChipModel() {
    return ESP.getChipModel();
}

const char* SystemMonitor::getSdkVersion() {
    return ESP.getSdkVersion();
}

uint32_t SystemMonitor::getFlashChipSize() {
    return ESP.getFlashChipSize();
}

uint32_t SystemMonitor::getFlashChipSpeed() {
    return ESP.getFlashChipSpeed();
}

FlashMode_t SystemMonitor::getFlashChipMode() {
    return ESP.getFlashChipMode();
}

uint64_t SystemMonitor::getEfuseMac() {
    return ESP.getEfuseMac();
}

// RAM info
uint32_t SystemMonitor::getHeapSize() {
    return ESP.getHeapSize();
}

uint32_t SystemMonitor::getFreeHeap() {
    return ESP.getFreeHeap();
}

uint32_t SystemMonitor::getMinFreeHeap() {
    return ESP.getMinFreeHeap();
}

uint32_t SystemMonitor::getMaxAllocHeap() {
    return ESP.getMaxAllocHeap();
}

// SPIRAM info
uint32_t SystemMonitor::getPsramSize() {
    return ESP.getPsramSize();
}

uint32_t SystemMonitor::getFreePsram() {
    return ESP.getFreePsram();
}

uint32_t SystemMonitor::getMinFreePsram() {
    return ESP.getMinFreePsram();
}

uint32_t SystemMonitor::getMaxAllocPsram() {
    return ESP.getMaxAllocPsram();
}

// Sketch info
uint32_t SystemMonitor::getSketchSize() {
    return ESP.getSketchSize();
}

uint32_t SystemMonitor::getFreeSketchSpace() {
    return ESP.getFreeSketchSpace();
}

String SystemMonitor::getSketchMD5() {
    return ESP.getSketchMD5();
}

StorageInfo SystemMonitor::getLittleFSInfo() {
    StorageInfo fs_info;
    fs_info.totalBytes = LittleFS.totalBytes();
    fs_info.usedBytes = LittleFS.usedBytes();
    return fs_info;
}


StorageInfo SystemMonitor::getSDInfo() {
    StorageInfo fs_info;
    fs_info.totalBytes = SD.totalBytes();
    fs_info.usedBytes = SD.usedBytes();
    return fs_info;
}

// Uptime info
unsigned long SystemMonitor::getUptime() {
    return millis();
}

String SystemMonitor::getSystemMonitorJson() {
    DynamicJsonDocument doc(1024);

    // CPU info
    doc["cpu"]["cores"] = getChipCores();
    doc["cpu"]["revision"] = getChipRevision();
    doc["cpu"]["model"] = getChipModel();
    doc["cpu"]["sdk_version"] = getSdkVersion();
    doc["cpu"]["flash_chip_size"] = getFlashChipSize();
    doc["cpu"]["flash_chip_speed"] = getFlashChipSpeed();
    doc["cpu"]["flash_chip_mode"] = getFlashChipMode();
    doc["cpu"]["efuse_mac"] = getEfuseMac();

    // RAM info
    doc["ram"]["heap_size"] = getHeapSize();
    doc["ram"]["free_heap"] = getFreeHeap();
    doc["ram"]["min_free_heap"] = getMinFreeHeap();
    doc["ram"]["max_alloc_heap"] = getMaxAllocHeap();

    // SPIRAM info
    doc["spiram"]["psram_size"] = getPsramSize();
    doc["spiram"]["free_psram"] = getFreePsram();
    doc["spiram"]["min_free_psram"] = getMinFreePsram();
    doc["spiram"]["max_alloc_psram"] = getMaxAllocPsram();

    // Sketch info
    doc["sketch"]["size"] = getSketchSize();
    doc["sketch"]["free_space"] = getFreeSketchSpace();
    doc["sketch"]["md5"] = getSketchMD5();

    // File system info
    doc["spiffs"]["total_bytes"] = getLittleFSInfo().totalBytes;
    doc["spiffs"]["used_bytes"] = getLittleFSInfo().usedBytes;
    doc["sd"]["total_bytes"] = getSDInfo().totalBytes;
    doc["sd"]["used_bytes"] = getSDInfo().usedBytes;

    // Uptime info
    doc["uptime"] = getUptime();

    String output;
    serializeJson(doc, output);
    return output;
}
#endif // SYSTEM_MONITOR_H
