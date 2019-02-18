#include <WiFi.h>
#include <HTTPClient.h>
#include "wlan_credentials.h"
#include "ogc_thing.h"
#include "ogc_constants.h"
#include "ArduinoJson.h"
#include "Thing.h"
#include "Location.h"
#include "Sensor.h"

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

const char* test = OGC_thing::primer;

//Create global Entities for Testing

//Thing
String thing_name = "Feinstaubmesser";
String thing_description = "Gerät zur Feinstaubmessung";
String thing_id = "A8:B9:C1";
Thing myThing(thing_name, thing_description, thing_id);

//Location
String location_name = "TECO";
String location_description = "Forschungsinstitut";
String encoding_type = "application/vnd.geo+json";
float location[] = {45.22, 39.55};
String location_id = "geo:teco:id:01";
Location myLocation(location_name, location_description, encoding_type, location);


//Location
String sensor_name = "SDS011";
String sensor_description = "Feinstaubsensor";
String sensor_encodingType = "application/pdf";
String sensor_metadata = "https://www.watterott.com/media/files_public/pkkwioshm/SDS011.pdf";
String sensor_id = "test:sds011:id:01";
Sensor mySensor(sensor_name, sensor_description, sensor_encodingType, sensor_metadata);
  
void connectToWLAN() {
  long currentTime = millis();
  long maxAllowedTime = currentTime+WLAN_TIMEOUT_MS;
  Serial.println("Establishing connection to WiFi..");
  WiFi.begin(ssid, password);
  
  while (true) {
    if(WiFi.status() != WL_CONNECTED) {
      if(millis() > maxAllowedTime) {
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

void printMAC() {
  Serial.print("MAC: ");
  Serial.print(esp32_MAC[5],HEX);
  Serial.print(":");
  Serial.print(esp32_MAC[4],HEX);
  Serial.print(":");
  Serial.print(esp32_MAC[3],HEX);
  Serial.print(":");
  Serial.print(esp32_MAC[2],HEX);
  Serial.print(":");
  Serial.print(esp32_MAC[1],HEX);
  Serial.print(":");
  Serial.println(esp32_MAC[0],HEX);
}

void setup() {
  
  Serial.println("Setup ...");
  Serial.begin(115200);
  char* charbuffer[100];
  size_t n = sizeof(charbuffer) / sizeof(charbuffer[0]);
  myThing.setLocationId("92b9c638-33a5-11e9-a534-77f46fab79ff");
  myLocation.setSelfId(location_id);
  mySensor.setSelfId(sensor_id);
  
  
  Serial.println("Setup completed!");
  
  
  


}

void loop() {
  
    if(program_state == WLANX_CONNECT) {
      connectToWLAN();
    }
    if (program_state == WLANX_ERROR) {
      Serial.println("WLAN Error");
    }
    if(program_state == THINGS_SERVER_PROBING) {
      http.begin("http://smartaqnet-dev.teco.edu:8080/FROST-Server/v1.0/");
      int httpCode = http.GET();
      if(httpCode < 0) {
        program_state = HTTP_REQUEST_ERROR;
        Serial.println("Error on HTTP request");
      }
      else if(httpCode != 200) {
        program_state = THINGS_SERVER_ERROR;
        Serial.println("Error on HTTP request");
      }
      else {
        Serial.println("Things Server Ready");
        program_state = THINGS_CREATE_STRUCTURE; //check if the structure has already been created, entweder im EEPROM oder per server request
      }
    }
    if(program_state == IDLE_) {
      //arm sensors
    }
    if(program_state == THINGS_CREATE_STRUCTURE) {
      Serial.println("Create things structure");
      //postThing(Serial);
      /*create the things we need laterly, THING, SENSOR, OBSERVERD_PROPERTY, LOCATION (inside/inline THINGS), DATASTREAM
       * for testing use dummy IDs for Sensors
       * USE MAC fpr THING
       * If one creation of a Entity fails abort
       */
      int httpCode;
      Serial.println("Thing");  
      char jsonbuffer[400];
      size_t j = sizeof(jsonbuffer) / sizeof(jsonbuffer[0]);
      Serial.println("jsonbuffersize = "+String(j));  
      myThing.toJSONString(jsonbuffer, j);

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
      myLocation.toJSONString(jsonbuffer, j);

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
      http.end(); 


      Serial.println("Sensor");  
      mySensor.toJSONString(jsonbuffer, j);

      Serial.println(jsonbuffer);  
      //Serial.println(String(n));
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
      */
    }
    
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

    http.end(); //Free the resources
  }*/

  delay(10000);

}
