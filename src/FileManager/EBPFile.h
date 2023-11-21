// EBPFile.h
#ifndef EBP_FILE_H
#define EBP_FILE_H

#include <Arduino.h>
#if defined(ESP32)
  #include <LittleFS.h>
#elif defined(ESP8266)
  #include <FS.h>
#endif
#include <SD.h>
#include "../Context.h"
#include "../Config/System/SystemConfigKeys.h"
#include "IEBPFile.h"


class EBPFile : public IEBPFile {
private:
  StorageType _storageType;
public:
    Context* context;
    EBPFile(Context* cntxt, StorageType storage_type) : context(cntxt), _storageType(storage_type) {
      initialize();
      
    }

    EBPFile(Context* cntxt, File file, StorageType storage_type): EBPFile(cntxt, storage_type){
      internalFile = file;
    }

    void initialize() override {
      begin();
    }

    void setInternalFile(const File& file) {
        internalFile = file;
    }

    size_t write(uint8_t val) override {
        size_t result = internalFile.write(val);
        // Add your code here.
        return result;
    }

    std::vector<FileData> Browse(String path) override{
        initialize();
        bool db_files = false;
        std::vector<FileData> file_datas = std::vector<FileData>();
        File root;
        if (_storageType == SPIFFS_TYPE) {
            if (path == "/db/")
            {
              path = "/";
              db_files = true;
            }
            
            root = LittleFS.open(path.c_str());
        } else if (_storageType == SD_TYPE) {
            root = SD.open(path.c_str());
        }
        if(root){
          File file = root.openNextFile();
          while(file){
              Serial.print("file = ");Serial.println(file.name());
              if (((String(file.name()).endsWith(".db") && !db_files) || (!String(file.name()).endsWith(".db") && db_files)) && _storageType == SPIFFS_TYPE)
              {
                file = root.openNextFile();
                continue;
              }              
              FileData fileData = FileData(file.name(), file.size(), true, file.size() == 0 ? true : false);
              file_datas.push_back(fileData);
              file = root.openNextFile();
          }
          if (_storageType == SPIFFS_TYPE && !db_files)
          {
            FileData fileData = FileData("db", 0, false, false);
            file_datas.push_back(fileData);                
          }
        }

        return file_datas;
    }


    IEBPFile* open(String _path, String mode) override {
      path = _path;
      // initialize();

      if (_storageType == SPIFFS_TYPE) {
        internalFile = LittleFS.open(path.c_str(), mode.c_str());
      } else if (_storageType == SD_TYPE) {
        internalFile = SD.open(path.c_str(), mode.c_str());
      }
      return this;
    }

    bool begin() {
      // return LittleFS.begin(true);
      if (_storageType == SPIFFS_TYPE) {
        #if defined(ESP32)
          return true;
          // return LittleFS.begin();
        #elif defined(ESP8266)
          return LittleFS.begin();
        #endif
      } else if (_storageType == SD_TYPE) {
        return SD.begin();
      }
      return false;
    }

    bool exists(String path) {
      if (_storageType == SPIFFS_TYPE) {
        return LittleFS.exists(path);
      } else if (_storageType == SD_TYPE) {
        return SD.exists(path);
      }
      return false;
    }

    bool remove(String path) {
      internalFile.close();
      if (_storageType == SPIFFS_TYPE) {
        return LittleFS.remove(path);
      } else if (_storageType == SD_TYPE) {
        return SD.remove(path);
      }
      return false;
    }

    bool rename(String pathFrom, String pathTo) {
      if (_storageType == SPIFFS_TYPE) {
        return LittleFS.rename(pathFrom, pathTo);
      } else if (_storageType == SD_TYPE) {
        return SD.rename(pathFrom, pathTo);
      }
      return false;
    }

    bool end() {
      if (_storageType == SPIFFS_TYPE) {
        #if defined(ESP32)
          LittleFS.end();
          return true;
        #elif defined(ESP8266)
          LittleFS.end();
          return true;
        #endif
      } else if (_storageType == SD_TYPE) {
        // There is no explicit end() function for SD, but you could add any cleanup code here if necessary.
        return true;
      }
      return false;
    }
    
    void close() override {
        internalFile.close();
    }

    operator bool() override {
        return static_cast<bool>(internalFile);
    }

    String name() override {
        return internalFile.name();
    }

    int available() override {
        return internalFile.available();
    }

    int peek() override {
        return internalFile.peek();
    }

    void flush() override {
        internalFile.flush();
    }

    int read() override {
        return internalFile.read();
    }

    size_t readBytes(char *buffer, size_t length) override {
        return internalFile.readBytes(buffer, length);
    }

    String readString() override {
        return internalFile.readString();
    }

    String readStringUntil(char terminator) override {
        return internalFile.readStringUntil(terminator);
    }

    long position() override {
        return internalFile.position();
    }

    bool seek(uint32_t pos) override {
        return internalFile.seek(pos);
    }

    long size() override {
        return internalFile.size();
    }

    bool isDirectory() override {
        return internalFile.isDirectory();
    }

    bool createDirectory(String path) override {
      if (_storageType == StorageType::SD_TYPE)
      {
        return LittleFS.mkdir(path);
      } else if (_storageType == SD_TYPE) {
        return SD.mkdir(path);
      }      
    }

    IEBPFile* openNextFile(String mode) override {
        internalFile = internalFile.openNextFile(mode.c_str());
        return this;
    }

    void rewindDirectory() override {
        internalFile.rewindDirectory();
    }

    bool isFile() override {
        return !internalFile.isDirectory();
    }

    size_t getSize() override {
        return internalFile.size();
    }

    size_t print(const __FlashStringHelper * str) override {
        return internalFile.print(str);
    }

    size_t print(const String & str) override {
        return internalFile.print(str);
    }

    size_t println(const String & str) override {
        return internalFile.println(str);
    }

    size_t print(const char str[]) override {
        return internalFile.print(str);
    }

    bool format() override {
        if (_storageType == SPIFFS_TYPE) {
            #if defined(ESP32)
                return LittleFS.format();
            #elif defined(ESP8266)
                // ESP8266's LittleFS library does not have a format() function.
                return false;
            #endif
        } else if (_storageType == SD_TYPE) {
            // SD library does not have a format() function.
            return false;
        }
        return false;
    }

    bool move(String dest) override {
        if (rename(internalFile.name(), dest.c_str())) {
            internalFile.close();
            open(dest, "r");
            return true;
        }
        return false;
    }

    bool copy(String dest) override {
        File destFile;

        if (_storageType == SPIFFS_TYPE) {
            destFile = LittleFS.open(dest, "w");
        } else if (_storageType == SD_TYPE) {
            destFile = SD.open(dest, "w");
        }

        if (!destFile) {
            return false;
        }

        internalFile.seek(0);

        while (internalFile.available()) {
            destFile.write(internalFile.read());
        }

        destFile.close();
        return true;
    }

    bool duplicate() override {
        String path = internalFile.path();
        int dotIndex = path.lastIndexOf('.');
        
        // If a dot is found, add "-Copy" before the file extension
        if (dotIndex >= 0) {
          String newPath = path.substring(0, dotIndex) + "-Copy" + path.substring(dotIndex);
          
          // Pass the new path to the copy function
          return copy(newPath);
        }
        
        return false;
    }

    bool mkdir(String path) override {
        return LittleFS.mkdir(path);
    }

};

#endif // EBP_FILE_H
