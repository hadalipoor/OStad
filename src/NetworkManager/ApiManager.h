#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <HTTPClient.h>  // Include the HTTPClient library for network operations

class ApiManager
{
private:

public:
    ApiManager();
    ~ApiManager();

    String makeGetRequest(String endpoint);
    String makePostRequest(String endpoint, String postData);
    String makePutRequest(String endpoint, String putData);
    String makeDeleteRequest(String endpoint);
    String urlEncode(String s);
};

ApiManager::ApiManager()
{
}

ApiManager::~ApiManager()
{
}

String ApiManager::makeGetRequest(String endpoint) {
    HTTPClient http;
    http.begin(endpoint); // Start connection
    int httpCode = http.GET(); // Send the request
    String payload = (httpCode > 0) ? http.getString() : ""; // Get the response payload
    http.end(); // End connection
    return payload;
}

String ApiManager::makePostRequest(String endpoint, String postData) {
    HTTPClient http;
    http.begin(endpoint);  // Begin connection
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Specify content-type header

    http.setConnectTimeout(100000);
    http.setTimeout(100000);
    int httpCode = http.POST(""); // Send the request

    String response = http.getString(); // Get the response payload

    http.end(); // Close connection
    return response;
}


String ApiManager::makePutRequest(String endpoint, String putData) {
    HTTPClient http;
    http.begin(endpoint);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.PUT(putData); // Send the PUT request
    String payload = (httpCode > 0) ? http.getString() : "";
    http.end();
    return payload;
}

String ApiManager::makeDeleteRequest(String endpoint) {
    HTTPClient http;
    http.begin(endpoint);
    int httpCode = http.sendRequest("DELETE"); // Send the DELETE request
    String payload = (httpCode > 0) ? http.getString() : "";
    http.end();
    return payload;
}

String ApiManager::urlEncode(String s) {
  String encoded = "";

  char c;
  char code0;
  char code1;
  char code2;
  for (unsigned int i = 0; i < s.length(); i++) {
    c = s.charAt(i);
    if (c == ' ') {
      encoded += '+';
    } else if (isalnum(c)) {
      encoded += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encoded += '%';
      encoded += code0;
      encoded += code1;
    }
  }
  return encoded;
}

#endif // APIMANAGER_H
