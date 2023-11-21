#ifndef IERRORHANDLER_H
#define IERRORHANDLER_H

#include <string>

enum ErrorType {
    FileOpenError,
    InvalidQuery,
    InvalidColumnName,
    CustomError,
    TableDoesNotExist,
    CalibrationSensorTriggeredWhileNotMoving,
};

class IErrorHandler {
public:
    virtual ~IErrorHandler() {}

    virtual void handleError(ErrorType error, const String& customMessage) = 0;
    virtual void handleError(ErrorType error) = 0;
    virtual void handleError(const String& errorMessage) = 0;
};

#endif // IERRORHANDLER_H
