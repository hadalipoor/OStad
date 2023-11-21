#ifndef ISYSTEMCONFIG_H
#define ISYSTEMCONFIG_H

#include <Arduino.h>

class IConfig {
public:
    virtual void initialize() = 0;
    virtual String get(const String& key) = 0;
    virtual void set(const String& key, const String& value) = 0;
};

#endif // ISYSTEMCONFIG_H
