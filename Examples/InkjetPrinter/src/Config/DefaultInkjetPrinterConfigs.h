
#ifndef DEFAULTINKJETPRINTER_H
#define DEFAULTINKJETPRINTER_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultInkjetPrinterConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultInkjetPrinterConfigs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in InkjetPrinter Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultInkjetPrinterConfigs::jsonString = R"(
{
    "active_template" : "",
    "printer_status" : "on",
    "printer_auto_on" : "off",
    "encoder_mode" : "internal",
    "printspeed" : "300",
    "encoder_steps" : "40",
    "print_mirror" : "off",
    "ink_opacity" : "3",
    "login_required" : "false",
    "login_username" : "admin",
    "login_password" : "admin",
    "total_print_count" : "0",
    "frimware_version" : "1.0.0",
    "frimware_update_date" : "2023-08-10 12:57:10",
    "printer_name" : "AIVWA Industrial Inkjet Printer - Serie H",
    "printer_serial" : "0",
    "repeat_line_print" : "5",
    "delay_afte_printhead_enable" : "1000",
    "delay_between_lines" : "1000",
    "delay_between_left_right" : "100",
    "delay_between_documents" : "500000"
}
)";

#endif
