#include <WiFi.h>
#include <HTTPClient.h>
#include "wlan_credentials.h"
#include "ogc_thing.h"
#include "ogc_constants.h"
#include "ArduinoJson.h"
/*#include "Thing.h"
#include "Location.h"
#include "Sensor.h"
#include "Datastream.h"
#include "FeatureOfInterest.h"
#include "librest/ObservedProperty.h"*/

#include "src/librest/rest_entities.h"

#include "entity_naming.h"
#include "frost_id_creator.h"

/*#include "src/librest/Thing.h"
#include "src/librest/Location.h"
#include "src/librest/Sensor.h"
#include "src/librest/Datastream.h"
#include "src/librest/FeatureOfInterest.h"
#include "src/librest/ObservedProperty.h"*/


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
String thing_id = "saqn:esp32:dev:jan:thing:01";
Thing myThing(thing_name, thing_description, thing_id);

//Location
String location_name = "TECO";
String location_description = "Forschungsinstitut";
String encoding_type = "application/vnd.geo+json";
float location[] = {45.22, 39.55};
String location_id = "geo:teco:id:01";
Location myLocation(location_name, location_description, encoding_type, location);


//Sensor
String sensor_name = "SDS011";
String sensor_description = "Feinstaubsensor";
String sensor_encodingType = "application/pdf";
String sensor_metadata = "https://www.watterott.com/media/files_public/pkkwioshm/SDS011.pdf";
String sensor_id = "saqn:esp32:dev:jan:sensor:01";
Sensor mySensor(sensor_name, sensor_description, sensor_encodingType, sensor_metadata);

//Datastream
String datastream_name = "PM10 datastream of virtual SDS011";
String datastream_description = "A datastream measuring dust";
String datastream_observationType = "http://www.opengis.net/def/observationType/OGCOM/2.0/OM_Measurement";

String unitOfMeasurement_name = "microgram per cubic meter";
String unitOfMeasurement_symbol = "ug/m^3";
String unitOfMeasurement_definition = "https://en.wikipedia.org/wiki/Particulates";

String datastream_id = "saqn:esp32:dev:jan:datastream:01";
Datastream myDatastream(datastream_name, datastream_description, datastream_observationType);

//Feature of Interest
String featureOfInterest_name = "TECO";
String featureOfInterest_description = "KIT Campus SUED, TECO";
String featureOfInterest_encodingType = "application/vnd.geo+json";
String featureOfInterest_id = "saqn:esp32:dev:jan:foi:01";
String featureOfInterest_feature_type = "Point";
FeatureOfInterest myFeatureOfInterest(featureOfInterest_name, featureOfInterest_description, featureOfInterest_encodingType);

//ObservedProperty
String observedProperty_name = "PM10";
String observedProperty_description = "Fine dust concentration";
String observedProperty_definition = "https://en.wikipedia.org/wiki/Particulates";
String observedProperty_id = "saqn:esp32:dev:jan:property:01";
ObservedProperty myObservedProperty(observedProperty_name, observedProperty_description, observedProperty_definition);


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
  
  myDatastream.setSelfId(datastream_id);
  myDatastream.setUnitOfMeasurement(unitOfMeasurement_name, unitOfMeasurement_symbol, unitOfMeasurement_definition);
  myDatastream.setObservedPropertyId(observedProperty_id);
  myDatastream.setSensorId(sensor_id);
  myDatastream.setThingId(thing_id);

  myFeatureOfInterest.setSelfId(featureOfInterest_id);
  float coordinates[] = {1.23, 9.87};
  myFeatureOfInterest.setFeature("Point", coordinates);

  myObservedProperty.setSelfId(observedProperty_id);
  Serial.println(teco::development::thing::primer);
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
      char jsonbuffer[600];
      size_t j = sizeof(jsonbuffer) / sizeof(jsonbuffer[0]);
      Serial.println("jsonbuffersize = "+String(j));
      
      /*Serial.println("Thing");  
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
      http.end();*/

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
      http.end(); */


      /*Serial.println("Sensor");  
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
      http.end();*/


      /*Serial.println("Datastream");  
      myDatastream.toJSONString(jsonbuffer, j);

      Serial.println(jsonbuffer);  
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

    Serial.println("ObservedProperty");
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
