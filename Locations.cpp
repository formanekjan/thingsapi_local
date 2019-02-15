#include "Locations.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Locations::Locations() {
  
}

void Locations::toJSONString(char* jsonString) {
  Serial.print("Create JSON");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  
  JsonArray* pointArray = NULL;
  pointArray = &jsonBuffer.createArray();
  pointArray->add(location[0]);
  pointArray->add(location[1]);

  JsonObject& locationObj = jsonBuffer.createObject(); 
  locationObj["coordinates"] = *pointArray;
  locationObj["type"] = "Point"; 
  
  JsonObject& locationsArrayEntry = jsonBuffer.createObject();
  locationsArrayEntry["location"] = locationObj;
  
  JsonArray& locationsArray = jsonBuffer.createArray();
  

  
}
