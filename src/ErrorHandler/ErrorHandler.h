// ErrorHandler.h

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <string>
#include "IErrorHandler.h"

class ErrorHandler : public IErrorHandler {
public:

    void handleError(ErrorType error, const String& customMessage = "") override{
    switch (error) {
      case FileOpenError:
        Serial.println("Error: Failed to open the file.");
        break;
      case InvalidQuery:
        Serial.println("Error: Invalid query format.");
        break;
      case InvalidColumnName:
        Serial.println("Error: Invalid column name.");
        break;
      case CustomError:
        Serial.println("Error: " + customMessage);
        break;
      default:
        Serial.println("Error: Unknown error.");
    }
  }

    void handleError(const String& errorMessage) override {
        handleError(ErrorType::CustomError, errorMessage);
    }

  void handleError(ErrorType error) override {
    handleError(error, "");
  }
};

#endif // ERRORHANDLER_H
