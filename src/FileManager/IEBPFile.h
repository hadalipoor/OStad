// IEBPFile.h
#ifndef IEBP_FILE_H
#define IEBP_FILE_H

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <SD.h>
#include "FileData.h"

enum StorageType {
  SPIFFS_TYPE,
  SD_TYPE
};

class IEBPFile {
public:
    virtual ~IEBPFile() {}
    File internalFile;
    String path;
    
    virtual void initialize() = 0;

    virtual size_t write(uint8_t val) = 0;

    virtual bool begin() = 0;

    virtual IEBPFile* open(String path, String mode) = 0;

    virtual std::vector<FileData> Browse(String path) = 0;

    virtual bool exists(String path) = 0;

    virtual bool remove(String path) = 0;

    virtual bool rename(String pathFrom, String pathTo) = 0;

    virtual bool end() = 0;

    virtual void close() = 0;
    virtual operator bool() = 0;
    virtual String name() = 0;

    virtual int available() = 0;
    virtual int peek() = 0;
    virtual void flush() = 0;
    virtual int read() = 0;
    virtual size_t readBytes(char *buffer, size_t length) = 0; // Reads characters from the file into buffer
    virtual String readString() = 0; // Reads a string from the file
    virtual String readStringUntil(char terminator) = 0; // Reads a string from the file until a specific character
    virtual long position() = 0; // Get the current position within the file
    virtual bool seek(uint32_t pos) = 0; // Set the position within the file
    virtual long size() = 0; // Get the size of the file
    virtual bool createDirectory(String path) = 0; // create a directory
    virtual bool isDirectory() = 0; // Check if the current file object is a directory
    virtual IEBPFile* openNextFile(String mode) = 0;
    virtual void rewindDirectory() = 0; // Resets a directory listing to the start
    virtual bool isFile() = 0;
    virtual size_t getSize() = 0;
    virtual size_t print(const __FlashStringHelper *) = 0;
    virtual size_t print(const String &) = 0;
    virtual size_t println(const String &) = 0;
    virtual size_t print(const char[]) = 0;    
    virtual bool format() = 0;
    virtual bool move(String dest) = 0;
    virtual bool copy(String dest) = 0;
    virtual bool duplicate() = 0;
    virtual bool mkdir(String path) = 0;

    static StorageType getStorageType(String storageTypeStr)
    {
      if (storageTypeStr == "SPIFFS_TYPE")
      {
        return StorageType::SPIFFS_TYPE;
      } 
      else if (storageTypeStr == "SD_TYPE")
      {
        return StorageType::SD_TYPE;
      }
      return StorageType::SPIFFS_TYPE;      
    }

};

#endif // IEBP_FILE_H
