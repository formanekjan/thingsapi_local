#ifndef THING
#define THING

#include <Arduino.h>

class Thing 
{ 
 private: 
  String name_; 
  String description; 
  String locationId;
  String serialNumber; 
  bool locationIdSet = false;
 public:
  //Thing();  
  Thing(String name_, String description, String serialNumber);
  void setLocationId(String locationId);
  void toJSONString(char* jsonString, size_t length_);
  
}; 

#endif