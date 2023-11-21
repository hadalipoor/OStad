#ifndef SIMCARDMANAGER_H
#define SIMCARDMANAGER_H

#include <Arduino.h>
#include <HardwareSerial.h>

using MessageCallback = std::function<void(String, String)>;

class SimCardManager
{
public:
    SimCardManager(int rxPin, int txPin) : _sim800(1), _rxPin(rxPin), _txPin(txPin), _lastMillis(0) 
    {
      initialize();
    }

    void initialize() {
        _sim800.begin(4800, SERIAL_8N1, _rxPin, _txPin); // RX, TX
        delay(1000);
        _sim800.println("AT");
        delay(1000);
        _sim800.println("AT+CMGF=1");
        delay(1000);
        _sim800.println("AT+CNMI=1,2,0,0,0");
        delay(1000);
        // Other initialization can be added here
    }

void update() {
  if (_sim800.available() && millis() - _lastMillis > 1000) {
    String response = _sim800.readString();
    Serial.println(response);

    // parse the response, extract phone number and message
    String phoneNumber = ""; 
    String message = ""; 

    // check if the response contains "+CMT:"
    int indexCMT = response.indexOf("+CMT:");
    if (indexCMT != -1) {
      int indexFirstQuote = response.indexOf("\"", indexCMT);
      int indexSecondQuote = response.indexOf("\"", indexFirstQuote + 1);
      
      // extract the phone number
      phoneNumber = response.substring(indexFirstQuote + 1, indexSecondQuote);
      
      // extract the message
      int indexNewLine = response.indexOf("\n", indexSecondQuote);
      if (indexNewLine != -1) {
        message = response.substring(indexNewLine + 1);
        message.trim();  // remove leading/trailing whitespaces
      }
    }

    if (_onMessageReceived && phoneNumber != "" && message != "") {
      _onMessageReceived(phoneNumber, message);
    }

    _lastMillis = millis();
  }
}

    bool sendMessage(String phoneNumber, String message) {
        _sim800.println("AT+CMGF=1"); // set to SMS mode
        _sim800.print("AT+CMGS=\"");
        _sim800.print(phoneNumber);
        _sim800.println("\"");

        _sim800.println(message);
        _sim800.write(26); // send Ctrl+Z

        // here you could check if the message was sent successfully
        // return true if successful, false otherwise
        return true;
    }

    void setOnMessageReceived(MessageCallback function) {
        _onMessageReceived = function;
    }

private:
    HardwareSerial _sim800;
    int _rxPin, _txPin;
    unsigned long _lastMillis;
    MessageCallback _onMessageReceived;
};

#endif //SIMCARDMANAGER_H
