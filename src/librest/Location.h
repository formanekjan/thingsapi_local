#ifndef LOCATION
#define LOCATION
#include "ArduinoJson.h"
#include <Arduino.h>
#include "LocationEntry.h"

class Location
{ 
 protected: 
  String name_;
  String description;
  String encodingType;
  float location[2];
  String selfId;
  String thingId;
  LocationEntry* locationEntry;
  bool linkedToThing = false;
 public:
  Location(String name_, String description, String encodingType, float* location, LocationEntry* locationEntry);
  Location(String name_, String description, String encodingType, float* location);
  Location();
  void addLocationEntry(LocationEntry* locationEntry);
  void setSelfId(String selfId);
  void setThingId(String thingId);
  void toJSONObject(JsonObject& root);
  void toJSONString(char* jsonString, size_t length_);
  
}; 

#endif
