#ifndef OBSERVED_PROPERTY
#define OBSERVED_PROPERTY

#include <Arduino.h>

class ObservedProperty
{ 
 private: 
  String name_;
  String description;
  String definition;
 
  String selfId;
  
 public:
  ObservedProperty(String name_, String description, String definition);
  void setSelfId(String selfId);
  void toJSONString(char* jsonString, size_t length_);
  
}; 

#endif
