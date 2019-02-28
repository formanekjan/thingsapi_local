#include <WiFi.h>
#include <HTTPClient.h>
#include "wlan_credentials.h"
#include "ArduinoJson.h"


#include "src/librest/rest_entities.h"
#include "src/workshop_instances/workshop_entities.h"


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

const char* FROST_SERVER_URL = "http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0";
const char* OPERATOR_URL = "tec.edu";

String MAC = "AA:BB:CC:DD";

float coordinates[] = {8.24, 49.0, 0.0};
WorkshopLocationEntry myWorkshopLocationEntry(coordinates);
WorkshopLocation myWorkshopLocation("86150 Augsburg", &myWorkshopLocationEntry);

CrowdsensingNode myCrowdsensingNode(MAC); //Thing

BME280_Sensor mybme280Sensor("no serial");
SDS011_Sensor mySDS011Sensor("no serial");

ObservedProperty_PM2_5 property_pm2_5;
Datastream_PM2_5 datastream_pm2_5(&myCrowdsensingNode, &mySDS011Sensor, &property_pm2_5);

ObservedProperty_PM10 property_pm10;
Datastream_PM10 datastream_pm10(&myCrowdsensingNode, &mySDS011Sensor, &property_pm10);




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
  /*frostID::Thing* test2 = new frostID::Thing("Feinsaubmesser", "AA:BB:CC:DD:EE:FF");*/
  /*frostID myfrostID;
    //myfrostID.addThing(test2);*/
  /*myfrostID.addThing(new frostID::Thing("Feinsaubmesser", "01.01.1970", "AA:BB:CC:DD:EE:FF"));

    Serial.println("Thing Id: ");
    Serial.println(myfrostID.thing->getId());*/

  /*Thing basething("sensorknoten", "feinstaubmessung", "GG:HH", "iot:id");
    Serial.println("Basethings address: ");
    Serial.println((int)&basething);
    Serial.println("basething serial: ");
    Serial.println(basething.getSerialNumber());


    ThingInLocation locationThing("sensorfusion", "schalldaten", "zz:12", "iot:id");
    Serial.println("locationThing address: ");
    Serial.println((int)&locationThing);
    Serial.println("locationThing serial: ");
    Serial.println(locationThing.getSerialNumber());


    String MAC = "AA:BB:CC:DD";



    Serial.println("Things address: ");
    Serial.println((int)&myCrowdsensingNode);
    Serial.println("Things serial: ");
    Serial.println(myCrowdsensingNode.getSerialNumber());

    ObservedProperty_PM2_5 property_pm2_5;
    Datastream_PM2_5 datastream_pm2_5(&myCrowdsensingNode, &mybme280Sensor, &property_pm2_5);*/
  Serial.println("Setup completed!");





}

void loop() {

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
    //postThing(Serial);
    /*create the things we need laterly, THING, SENSOR, OBSERVERD_PROPERTY, LOCATION (inside/inline THINGS), DATASTREAM
       for testing use dummy IDs for Sensors
       USE MAC fpr THING
       If one creation of a Entity fails abort
    */
    int httpCode;
    char jsonbuffer[1000];
    size_t j = sizeof(jsonbuffer) / sizeof(jsonbuffer[0]);
    Serial.println("jsonbuffersize = " + String(j));

    /*Serial.println("Thing");
      myCrowdsensingNode.toJSONString(jsonbuffer, j);
      Serial.println(jsonbuffer);  */

    //Serial.println(String(n));
    /*http.end();
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
      http.end();*/

    /*Serial.println("Location");
      myWorkshopLocation.toJSONString(jsonbuffer, j);

      Serial.println(jsonbuffer);  */
    //Serial.println(String(n));
    /*http.end();
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

      Serial.println("Sensor 2");

      mySDS011Sensor.toJSONString(jsonbuffer, j);

      Serial.println(jsonbuffer); */


    //Serial.println(String(n));
    /*http.end();
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
      http.end();*/


    Serial.println("Datastream pm2_5");
    datastream_pm2_5.toJSONString(jsonbuffer, j);

    Serial.println(jsonbuffer);

    Serial.println("Datastream pm10");
    datastream_pm10.toJSONString(jsonbuffer, j);

    Serial.println(jsonbuffer);
    /*
      //Serial.println(String(n));
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

      }*/

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

      http.end(); //Free the resources*/
  }

  delay(10000);

}
