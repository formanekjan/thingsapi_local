#ifndef LOCATION
#define LOCATION

#include <Arduino.h>

class Location
{ 
 private: 
  String name_;
  String description;
  String encodingType;
  float* location;
  String selfId;
  String thingId;
  bool linkedToThing = false;
 public:
  Location(String name_, String description, String encodingType, float* location);
  void setSelfId(String selfId);
  void setThingId(String thingId);
  void toJSONString(char* jsonString, size_t length_);
  
}; 

#endif
