#include <WiFi.h>
#include <HTTPClient.h>
#include "wlan_credentials.h"
#include "ogc_thing.h"
#include "ogc_constants.h"

const char* FROST_SERVER_URL = "http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0";
const char* test = OGC_thing::primer;
//HTTPClient http;

void connectToNetwork() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Establishing connection to WiFi..");
  }

  Serial.println("Connected to network");
  //http.begin("http://jsonplaceholder.typicode.com/comments?id=10");

}

void setup() {
  
  Serial.begin(115200);
  Serial.println("Setup");
  connectToNetwork();

  
  

}

void loop() {
  
  
    if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;

    http.begin("http://jsonplaceholder.typicode.com/comments?id=10"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request

    if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }

  delay(10000);

}
