#include "Location.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Location::Location() {
}

Location::Location(String name_, String description, String encodingType, float* location, LocationEntry* locationEntry) {
  this->name_ = name_;
  this->description = description;
  this->encodingType = encodingType;
  this->location[0] = location[0];
  this->location[1] = location[1];
  this->locationEntry = locationEntry;
}

Location::Location(String name_, String description, String encodingType, float* location) {
  this->name_ = name_;
  this->description = description;
  this->encodingType = encodingType;
  this->location[0] = location[0];
  this->location[1] = location[1];
  this->locationEntry = locationEntry;
}

void Location::addLocationEntry(LocationEntry* locationEntry) {
  this->locationEntry = locationEntry;
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
  StaticJsonBuffer<512> jsonBuffer;

  root["name"] = name_;
  root["description"] = description;
  root["encodingType"] = encodingType;
  
  JsonArray* pointArray = NULL;
  pointArray = &jsonBuffer.createArray();
  pointArray->add(location[0]);
  pointArray->add(location[1]);

  JsonObject& locationObj = jsonBuffer.createObject(); 
  locationObj["type"] = "Point"; 
  locationObj["coordinates"] = *pointArray;
  

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
