#include "Location.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Location::Location(String name_, String description, String encodingType, float* location) {
  this->name_ = name_;
  this->description = description;
  this->encodingType = encodingType;
  this->location[0] = location[0];
  this->location[1] = location[1];
}

void Location::setSelfId(String selfId) {
  this->selfId = selfId;
}

void Location::setThingId(String thingId) {
  this->thingId = thingId;
  linkedToThing = true;
}

void Location::toJSONObject(JsonObject& root) {
  Serial.print("Create JSON");
  StaticJsonBuffer<256> jsonBuffer;

  root["name"] = name_;
  root["description"] = description;
  root["encodingType"] = encodingType;
  
  JsonArray* pointArray = NULL;
  pointArray = &jsonBuffer.createArray();
  pointArray->add(location[0]);
  pointArray->add(location[1]);

  JsonObject& locationObj = jsonBuffer.createObject(); 
  locationObj["coordinates"] = *pointArray;
  locationObj["type"] = "Point"; 

  root["location"] = locationObj;
  root["@iot.id"] = selfId;
  //root.printTo(jsonString, length_);
}

void Location::toJSONString(char* jsonString, size_t length_) {
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); 
  toJSONObject(root);
 
  root.printTo(jsonString, length_);

  
}
