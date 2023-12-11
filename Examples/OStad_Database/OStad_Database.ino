#define LOG_LEVEL_DEBUG
// #define OSTAD_NETWORK_DISABLE
// #define OSTAD_MODULES_DISABLE

#include <OStad.h>
#include "LightScheduleController.h"
#include "LightScheduleEntity.h"
OStad* ostad;

void setup() {
    Serial.begin(115200);
    LittleFS.begin();
    
    // Initialization code...
    ostad = new OStad(StorageType::SPIFFS_TYPE);

    // Initialize LightSchedule table controller
    LightScheduleController* lightScheduleController = new LightScheduleController(ostad->getContext(), StorageType::SPIFFS_TYPE);
    
    // Remove table if exists
    lightScheduleController->RemoveTable();
    
    // Add a new entity
    EBPDateTime exampleActionTime; // Assuming EBPDateTime has a way to set a specific time
    LightScheduleEntity* lightScheduleEntity = new LightScheduleEntity("Example Title", 1, true, exampleActionTime); // Example values
    int id = lightScheduleController->Add(*lightScheduleEntity);

    if (id != -1) {
        ostad->getContext()->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::USER_LOGS, "Entity added successfully.");
    } else {
        ostad->getContext()->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::USER_LOGS, "Failed to add entity.");
    }

    // GetById - Retrieve the entity
    LightScheduleEntity retrievedEntity = lightScheduleController->GetById(id);
    if (&retrievedEntity != nullptr) {
        ostad->getContext()->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::USER_LOGS, retrievedEntity.getTitle());
    } else {
        ostad->getContext()->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::USER_LOGS, "Failed to retrieve entity.");
    }

    // Update the entity
    retrievedEntity.setTitle("NewTitle"); // Example modification
    bool updateStatus = lightScheduleController->Update(retrievedEntity);
    if (updateStatus) {
        ostad->getContext()->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::USER_LOGS, "Entity updated successfully.");
        ostad->getContext()->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::USER_LOGS, retrievedEntity.getTitle());
    } else {
        ostad->getContext()->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::USER_LOGS, "Failed to update entity.");
    }

    // Simulate Get by Id in query
    String query = String(LightScheduleEntity::COLUMN_TITLE + "=NewTitle AND ") + LightScheduleEntity::COLUMN_RELAYSTATUS + String("=1");
    
    std::vector<LightScheduleEntity> queriedEntity = lightScheduleController->Get(query);
    if (queriedEntity.size() > 0) {
        ostad->getContext()->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::USER_LOGS, "Entity retrieved via query successfully.");
    } else {
        ostad->getContext()->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::USER_LOGS, "Failed to retrieve entity via query.");
    }

    // Delete the entity
    bool deleteStatus = lightScheduleController->Delete(id);
    if (deleteStatus) {
        ostad->getContext()->getLogger()->log(LogLevel::DEBUG_LEVEL, LogTitles::USER_LOGS, "Entity deleted successfully.");
    } else {
        ostad->getContext()->getLogger()->log(LogLevel::ERROR_LEVEL, LogTitles::USER_LOGS, "Failed to delete entity.");
    }

    ostad->begin();
}

void loop() {
  ostad->update();    
}
