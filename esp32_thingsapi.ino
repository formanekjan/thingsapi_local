#include <WiFi.h>
#include <HTTPClient.h>
#include "wlan_credentials.h"
#include "ArduinoJson.h"


#include "src/librest/rest_entities.h"
#include "src/workshop_instances/workshop_entities.h"
#include "src/librest/Frost_Server.h"
#include "src/librest/FrostManager.h"



boolean factoryfresh = false; //if the node hasn't been used before
const int WLAN_TIMEOUT_MS = 30000;
byte esp32_MAC[6];

enum States {
  WLANX_CONNECT,
  WLANX_ERROR,
  THINGS_SERVER_PROBING,
  THINGS_SERVER_ERROR,
  HTTP_REQUEST_ERROR,
  SENSORS_READING,
  THINGS_CREATE_STRUCTURE,
  IDLE_
};

States program_state = WLANX_CONNECT;
HTTPClient http;

//const char* FROST_SERVER_URL = "http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0";
const char* FROST_SERVER_URL = "http://192.168.1.34:8080/FROST-Server/v1.0";
const char* OPERATOR_URL = "tec.edu";

String MAC = "AA:BB:CC:DD";

float coordinates[] = {8.24, 49.0, 0.0};

WorkshopLocationEntry myWorkshopLocationEntry(coordinates);
WorkshopLocation myWorkshopLocation("86150 Augsburg", &myWorkshopLocationEntry);

CrowdsensingNode myCrowdsensingNode(MAC); 

/*BME280_Sensor mybme280Sensor("no serial");
SDS011_Sensor mySDS011Sensor("no serial");

ObservedProperty_PM2_5 property_pm2_5;
Datastream_PM2_5 datastream_pm2_5(&myCrowdsensingNode, &mySDS011Sensor, &property_pm2_5);

ObservedProperty_PM10 property_pm10;
Datastream_PM10 datastream_pm10(&myCrowdsensingNode, &mySDS011Sensor, &property_pm10);

ObservedProperty_Humidity property_Humidity;
Datastream_Humidity Datastream_Humidity(&myCrowdsensingNode, &mybme280Sensor, &property_Humidity);

ObservedProperty_Pressure property_Pressure;
Datastream_Pressure Datastream_Pressure(&myCrowdsensingNode, &mybme280Sensor, &property_Pressure);

ObservedProperty_Temperature property_Temperature;
Datastream_Temperature Datastream_Temperature(&myCrowdsensingNode, &mybme280Sensor, &property_Temperature);*/

FrostManager frostManager(MAC, "no", "no", coordinates, "Lilienweg 7b");

void printMAC() {
  Serial.print("MAC: ");
  Serial.print(esp32_MAC[5], HEX);
  Serial.print(":");
  Serial.print(esp32_MAC[4], HEX);
  Serial.print(":");
  Serial.print(esp32_MAC[3], HEX);
  Serial.print(":");
  Serial.print(esp32_MAC[2], HEX);
  Serial.print(":");
  Serial.print(esp32_MAC[1], HEX);
  Serial.print(":");
  Serial.println(esp32_MAC[0], HEX);
}

void connectToWLAN() {
  long currentTime = millis();
  long maxAllowedTime = currentTime + WLAN_TIMEOUT_MS;
  Serial.println("Establishing connection to WiFi..");
  WiFi.begin(ssid, password);

  while (true) {
    if (WiFi.status() != WL_CONNECTED) {
      if (millis() > maxAllowedTime) {
        program_state = WLANX_ERROR;
        break;
      }
    }
    else {
      Serial.println("Connected to network");
      WiFi.macAddress(esp32_MAC);
      printMAC();
      program_state = THINGS_SERVER_PROBING;
      break;
    }
  }
}





void setup() {

  Serial.println("Setup ...");
  Serial.begin(115200);
  char* charbuffer[100];
  size_t n = sizeof(charbuffer) / sizeof(charbuffer[0]);

  myCrowdsensingNode.addLocation(&myWorkshopLocation);
  Serial.println("Constants: ");
  Serial.println(FROST_Server::base_url);
  Serial.println(FROST_Server::things_url);
  Serial.println(FROST_Server::datastreams_url);
  Serial.println("Setup completed!");



}

void loop() {
  //frostManager.createEntities();

  if (program_state == WLANX_CONNECT) {
    connectToWLAN();
  }
  if (program_state == WLANX_ERROR) {
    Serial.println("WLAN Error");
  }
  if (program_state == THINGS_SERVER_PROBING) {
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/");
    int httpCode = http.GET();
    if (httpCode < 0) {
      program_state = HTTP_REQUEST_ERROR;
      Serial.println("Error on HTTP request");
    }
    else if (httpCode != 200) {
      program_state = THINGS_SERVER_ERROR;
      Serial.println("Error on HTTP request");
    }
    else {
      Serial.println("Things Server Ready");
      program_state = THINGS_CREATE_STRUCTURE; //check if the structure has already been created, entweder im EEPROM oder per server request
    }
  }
  if (program_state == IDLE_) {
    //arm sensors
  }
  if (program_state == THINGS_CREATE_STRUCTURE) {
    Serial.println("Create things structure");
    
    
    int httpCode;
    char jsonbuffer[2048];
    size_t j = sizeof(jsonbuffer) / sizeof(jsonbuffer[0]);
    Serial.println("jsonbuffersize = " + String(j));

    
    Serial.println("Thing");
    myCrowdsensingNode.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);  

    //Serial.println(String(n));
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Things");
    http.addHeader("Content-Type", "application/json");
    //int httpCode = http.POST(jsonbuffer);
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();

      /*Serial.println("Location");
      myWorkshopLocation.toJSONString(jsonbuffer, j);

      Serial.println(jsonbuffer);  
      //Serial.println(String(n));
      http.end();
      http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Locations");
      http.addHeader("Content-Type", "application/json");
      httpCode = http.POST(jsonbuffer);
      if(httpCode < 0) {
      program_state = HTTP_REQUEST_ERROR;
      Serial.println("Error on HTTP post");
      Serial.println("Code "+String(httpCode));
      }
      else {
      Serial.println("HTTP Code: "+String(httpCode));
      program_state = IDLE_;
      }
      http.end(); */


      /*Serial.println("Sensor 1");
      mybme280Sensor.toJSONString(jsonbuffer, j);

      Serial.println(jsonbuffer);

      //*Serial.println("Sensor 2");*/
      
      /*Serial.println("Sensor: SDS011");
      mySDS011Sensor.toJSONString(jsonbuffer, j);
      Serial.println(jsonbuffer); 
      
      http.end();
      http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Sensors");
      http.addHeader("Content-Type", "application/json");
      httpCode = http.POST(jsonbuffer);
      if(httpCode < 0) {
      program_state = HTTP_REQUEST_ERROR;
      Serial.println("Error on HTTP post");
      Serial.println("Code "+String(httpCode));
      }
      else {
      Serial.println("HTTP Code: "+String(httpCode));
      program_state = IDLE_;
      }
      http.end();

      Serial.println("Sensor: BME280");
      mybme280Sensor.toJSONString(jsonbuffer, j);
      Serial.println(jsonbuffer); 
      
      http.end();
      http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Sensors");
      http.addHeader("Content-Type", "application/json");
      httpCode = http.POST(jsonbuffer);
      if(httpCode < 0) {
      program_state = HTTP_REQUEST_ERROR;
      Serial.println("Error on HTTP post");
      Serial.println("Code "+String(httpCode));
      }
      else {
      Serial.println("HTTP Code: "+String(httpCode));
      program_state = IDLE_;
      }
      http.end();

    Serial.println("Observed Property PM2_5");
    property_pm2_5.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/ObservedProperties");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();
    
    
    Serial.println("Datastream pm2_5");
    datastream_pm2_5.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Datastreams");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();

    Serial.println("Observed Property PM10");
    property_pm10.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/ObservedProperties");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();

    Serial.println("Datastream pm10");
    datastream_pm10.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Datastreams");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();

    Serial.println("Property Humidity");
    property_Humidity.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/ObservedProperties");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();

    //Serial.println(String(n));
    
    Serial.println("Datastream Humidity");
    Datastream_Humidity.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Datastreams");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();

    
    //ObservedProperty_Pressure property_Pressure;
    //Datastream_Pressure Datastream_Pressure(&myCrowdsensingNode, &mybme280Sensor, &property_Pressure);

    Serial.println("Property Pressure");
    property_Pressure.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/ObservedProperties");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();


    Serial.println("Datastream Pressure");
    Datastream_Pressure.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Datastreams");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();

    Serial.println("Property Temperature");
    property_Temperature.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/ObservedProperties");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();
    

    Serial.println("Datastream Temperature");
    Datastream_Temperature.toJSONString(jsonbuffer, j);
    Serial.println(jsonbuffer);
    
    http.end();
    http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/Datastreams");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    program_state = HTTP_REQUEST_ERROR;
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    program_state = IDLE_;
    }
    http.end();
    
    /*Serial.println("Feature of Interest");
      myFeatureOfInterest.toJSONString(jsonbuffer, j);

      Serial.println(jsonbuffer);
      //Serial.println(String(n));
      http.end();
      http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/FeaturesOfInterest");
      http.addHeader("Content-Type", "application/json");
      httpCode = http.POST(jsonbuffer);
      if(httpCode < 0) {
      program_state = HTTP_REQUEST_ERROR;
      Serial.println("Error on HTTP post");
      Serial.println("Code "+String(httpCode));
      }
      else {
      Serial.println("HTTP Code: "+String(httpCode));
      program_state = IDLE_;
      }
      http.end();*/

    /*Serial.println("ObservedProperty");
      myObservedProperty.toJSONString(jsonbuffer, j);
      Serial.println(jsonbuffer);
      //Serial.println(String(n));
      http.end();
      http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/ObservedProperties");
      http.addHeader("Content-Type", "application/json");
      httpCode = http.POST(jsonbuffer);
      if(httpCode < 0) {
      program_state = HTTP_REQUEST_ERROR;
      Serial.println("Error on HTTP post");
      Serial.println("Code "+String(httpCode));
      }
      else {
      Serial.println("HTTP Code: "+String(httpCode));
      program_state = IDLE_;
      }
      http.end();


      }*/


    /*if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status



      http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/"); //Specify the URL
      //http.begin("http://jsonplaceholder.typicode.com/comments?id=10"); //Specify the URL
      int httpCode = http.GET();                                        //Make the request

      if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }

      else {
      Serial.println("Error on HTTP request");
      }

      http.end(); //Free the resources */
  }

  delay(10000);

}
