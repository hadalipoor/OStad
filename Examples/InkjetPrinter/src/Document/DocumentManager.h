/**
 * @file DocumentManager.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <ArduinoJson.h>
#include <vector>
#include "../AppContext.h"
#include "../Config/InkjetPrinterConfigKeys.h"

struct DocumentInfo {
  String name;
  String path;
  bool is_active;
  int print_count;
  String last_print_date;
  String created_date;
};

/**
 * @brief 
 * 
 */
class DocumentManager {
  private:
    AppContext* appContext;

  public:
    DocumentManager(AppContext* appContext);
    bool addDocument(JsonDocument& newDoc);
    bool editDocument(const char* docName, JsonDocument& updatedDoc);
    bool editDocumentSettings(String delay_before_print, String quantity, String quantity_delay, String name, String repeat_template);
    bool deleteDocument(const char* docName);
    bool duplicateDocument(const char* srcDocName, const char* destDocName);
    void setActivePrintDocument(String docName);
    String getActivePrintDocument();
    String getListOfDocumentsByString();
    String getDocumentByName(String name);
    std::vector<DocumentInfo> getListOfDocuments();
    const char* documentsFolder = "";
    String document_extention = ".iip";

};

DocumentManager::DocumentManager(AppContext* appContext): appContext(appContext) {}

// Add a new PrintDocument
bool DocumentManager::addDocument(JsonDocument& newDoc) {
  const char* docName = newDoc["document_name"];
  String docPath = String(documentsFolder) + "/" + docName + document_extention;
  if (appContext->systemContext->getLittleFS()->exists(docPath)) {
    return false;
  }

  appContext->systemContext->getLittleFS()->open(docPath, "w");
  
  serializeJson(newDoc, appContext->systemContext->getLittleFS()->internalFile);

  appContext->systemContext->getLittleFS()->close();
  return true;
}

/**
 * @brief Edit an existing PrintDocument
 * 
 * @param delay_before_print 
 * @param quantity 
 * @param quantity_delay 
 * @param name 
 * @param repeat_template 
 * @return true 
 * @return false 
 */
bool DocumentManager::editDocumentSettings(String delay_before_print, String quantity, String quantity_delay, String name, String repeat_template)
{
    String docPath = String(documentsFolder) + "/" + name + document_extention;
    if (!appContext->systemContext->getLittleFS()->exists(docPath)) {
        return false;
    }

    // Load the existing JSON document from the file
    appContext->systemContext->getLittleFS()->open(docPath, "r");
    DynamicJsonDocument doc(4096); // Assuming the document size is less than 4096 bytes
    deserializeJson(doc, appContext->systemContext->getLittleFS()->internalFile);
    appContext->systemContext->getLittleFS()->close();

    // Update the JSON document with the provided settings
    doc["delay_before_print"] = delay_before_print.toInt();
    doc["quantity"] = quantity.toInt();
    doc["quantity_delay"] = quantity_delay.toInt();
    doc["repeat_document"] = (repeat_template == "true" ? true : false);

    // Serialize the updated JSON document back to the file
    appContext->systemContext->getLittleFS()->open(docPath, "w");
    serializeJson(doc, appContext->systemContext->getLittleFS()->internalFile);
    appContext->systemContext->getLittleFS()->close();

    return true;
}

bool DocumentManager::editDocument(const char* docName, JsonDocument& updatedDoc) {
  String docPath = String(documentsFolder) + "/" + docName + document_extention;
  if (!appContext->systemContext->getLittleFS()->exists(docPath)) {
    return false;
  }

  if (!appContext->systemContext->getLittleFS()->exists(docPath)) {
    return false;
  }
  appContext->systemContext->getLittleFS()->open(docPath, "w");

  serializeJson(updatedDoc, appContext->systemContext->getLittleFS()->internalFile);
  appContext->systemContext->getLittleFS()->close();
  return true;
}

// Delete a PrintDocument
bool DocumentManager::deleteDocument(const char* docName) {
  String docPath = String(documentsFolder) + "/" + docName + document_extention;
  return appContext->systemContext->getLittleFS()->remove(docPath);
}

// Duplicate a PrintDocument
bool DocumentManager::duplicateDocument(const char* srcDocName, const char* destDocName) {
  String srcDocPath = String(documentsFolder) + "/" + srcDocName + document_extention;
  String destDocPath = String(documentsFolder) + "/" + destDocName + document_extention;

  if (!appContext->systemContext->getLittleFS()->exists(srcDocPath) || appContext->systemContext->getLittleFS()->exists(destDocPath)) {
    return false;
  }

  IEBPFile* srcDocFile = appContext->systemContext->getLittleFS()->open(srcDocPath, "r");
  IEBPFile* destDocFile = appContext->systemContext->getLittleFS()->open(destDocPath, "w");

  if (!srcDocFile || !destDocFile) {
    srcDocFile->close();
    destDocFile->close();
    return false;
  }

  size_t fileSize = srcDocFile->size();
  uint8_t buffer[64];
  size_t bytesRead;

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////

  //                                             FIX IT

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  // while ((bytesRead = srcDocFile->read(buffer, sizeof(buffer))) > 0) {
  //   destDocFile->write(buffer, bytesRead);
  // }

  // srcDocFile.close();
  // destDocFile.close();
  return true;
}

// Set the active_print_document in settings using PrinterSettings class
void DocumentManager::setActivePrintDocument(String docName) {
  appContext->getInkjetPrinterConfig()->set(InkjetPrinterConfigKey::ACTIVE_TEMPLATE, docName);
}

String DocumentManager::getDocumentByName(String name)
{
  String srcDocPath = String(documentsFolder) + "/" + name + document_extention;
  IEBPFile* active_template_file = appContext->systemContext->getLittleFS()->open(srcDocPath, "r");

  return active_template_file->readString();
}

String DocumentManager::getActivePrintDocument()
{
  String srcDocPath = String(documentsFolder) + "/" + appContext->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::ACTIVE_TEMPLATE) + document_extention;
  IEBPFile* active_template_file = appContext->systemContext->getLittleFS()->open(srcDocPath, "r");

  return active_template_file->readString();
}

// Get a list of all documents in storage
String DocumentManager::getListOfDocumentsByString() {
  DynamicJsonDocument docList(8192);
  JsonArray documents = docList.createNestedArray("documents");
  
  std::vector<FileData> files;
  if (storageType == StorageType::SPIFFS_TYPE)
  {
      files = appContext->systemContext->getLittleFS()->Browse("/");
  }
  else if (storageType == StorageType::SD_TYPE)
  {
      files = appContext->systemContext->getSD()->Browse("/");
  }     

  DynamicJsonDocument doc(2048);
  JsonArray array = doc.to<JsonArray>();

  for(int i = 0; i < files.size(); i++) {
      JsonObject obj = array.createNestedObject();
      if (!files[i].name.endsWith(document_extention))
      {
        continue;
      }
      String name = files[i].name;
      name.remove(name.indexOf(document_extention),4);
      obj["name"] = name;
      obj["path"] = "/";
      obj["is_active"] = name == appContext->getInkjetPrinterConfig()->get(InkjetPrinterConfigKey::ACTIVE_TEMPLATE);
      obj["print_count"] = obj["print_count"].as<int>();
      obj["last_print_date"] = obj["last_print_date"].as<const char*>();
      obj["created_date"] = obj["create_date"].as<const char*>();
      
      
      
      
  }
  
  
  String result;
  serializeJson(doc, result);
  return result;
}

std::vector<DocumentInfo> DocumentManager::getListOfDocuments() {
    String json = getListOfDocumentsByString();
    DynamicJsonDocument doc(4096);
    deserializeJson(doc, json);

    std::vector<DocumentInfo> documents;
    JsonArray jsonArray = doc["documents"];
    for (JsonObject jsonDoc : jsonArray) {
        DocumentInfo info;
        info.name = jsonDoc["name"].as<String>();
        info.path = jsonDoc["path"].as<String>();
        info.is_active = jsonDoc["is_active"].as<bool>();
        info.print_count = jsonDoc["print_count"].as<int>();
        info.last_print_date = jsonDoc["last_print_date"].as<String>();
        info.created_date = jsonDoc["created_date"].as<String>();
        documents.push_back(info);
    }

    return documents;
}

#endif // DOCUMENTMANAGER_H