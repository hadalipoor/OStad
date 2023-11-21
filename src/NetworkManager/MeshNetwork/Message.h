#ifndef MESSAGE_H
#define MESSAGE_H
// Message.h
#include <Arduino.h>
#include <map>

class Message {
public:
    uint32_t nodeId;
    String className;
    String functionName;
    std::map<String, String> parameters;
    String responseMessage;

    String toString() {
        if (responseMessage.length() > 0)
        {
            String queryString = nodeId + "/response=" + responseMessage;
            return queryString;
        }
        
        String queryString = nodeId + "/" + className + "/" + functionName + "?";
        for (auto const& pair : parameters) {
            queryString += pair.first + "=" + pair.second + "&";
        }
        // Remove the last "&"
        queryString = queryString.substring(0, queryString.length() - 1);
        return queryString;
    }

    void fromString(String queryString) {
        int firstSlash = queryString.indexOf('/');
        int responseStart = queryString.indexOf("response=", firstSlash + 1);
        if (responseStart != -1)
        {
            responseMessage = queryString.substring(responseStart + 9);
            return;
        }
        
        int secondSlash = queryString.indexOf('/', firstSlash + 1);
        int questionMark = queryString.indexOf('?');

        nodeId = queryString.substring(0, firstSlash).toInt();
        className = queryString.substring(firstSlash + 1, secondSlash);
        functionName = queryString.substring(secondSlash + 1, questionMark);

        String parametersString = queryString.substring(questionMark + 1);
        int nextAmpersand;
        do {
            nextAmpersand = parametersString.indexOf('&');
            String parameterPair = parametersString.substring(0, nextAmpersand);
            int equalsSign = parameterPair.indexOf('=');
            String parameterName = parameterPair.substring(0, equalsSign);
            String parameterValue = parameterPair.substring(equalsSign + 1);
            parameters[parameterName] = parameterValue;
            parametersString = parametersString.substring(nextAmpersand + 1);
        } while (nextAmpersand != -1);
    }
};
#endif