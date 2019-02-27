#include "WorkshopLocation.h"
#include "ArduinoJson.h"
#include <Arduino.h>

WorkshopLocation::WorkshopLocation(String name_, float* location) {
  this->name_ = name_;
  this->location[0] = location[0];
  this->location[1] = location[1];
  this->selfId = "geo:"+String(location[0])+","+String(location[1]);
  this->description = "";
  this->encodingType = "application/vnd.geo+json";
}



void WorkshopLocation::toJSONObject(JsonObject& root) {
  Serial.print("Create JSON");
  StaticJsonBuffer<512> jsonBuffer;

  root["name"] = name_;
  root["description"] = "";
  root["encodingType"] = "application/vnd.geo+json";
  
  JsonArray* pointArray = NULL;
  pointArray = &jsonBuffer.createArray();
  pointArray->add(location[0]);
  pointArray->add(location[1]);

  JsonObject& locationObj = jsonBuffer.createObject(); 
  locationObj["type"] = "Point"; 
  locationObj["coordinates"] = *pointArray;
  

  root["location"] = locationObj;
  root["@iot.id"] = selfId;
}

void WorkshopLocation::toJSONString(char* jsonString, size_t length_) {
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); 
  toJSONObject(root);
 
  root.printTo(jsonString, length_);

  
}
