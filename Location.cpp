#include "Location.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Location::Location(String name_, String description, String encodingType, float* location) {
  this->name_ = name_;
  this->description = description;
  this->encodingType = encodingType;
  this->location = location;
}

void Location::setSelfId(String selfId) {
  this->selfId = selfId;
}

void Location::setThingId(String thingId) {
  this->thingId = thingId;
  linkedToThing = true;
}

void Location::toJSONString(char* jsonString, size_t length_) {
  Serial.print("Create JSON");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts

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
  
  root.printTo(jsonString, length_);

  
}
