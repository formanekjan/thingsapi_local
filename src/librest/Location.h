#ifndef LOCATION
#define LOCATION

#include <Arduino.h>

class Location
{ 
 protected: 
  String name_;
  String description;
  String encodingType;
  float location[2];
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
