#ifndef SENSOR
#define SENSOR

#include <Arduino.h>

class Sensor
{ 
 private: 
  String name_;
  String description;
  String encodingType;
  String metadata;
  String selfId;
  
 public:
  Sensor(String name_, String description, String encodingType, String metadata);
  void setSelfId(String selfId);
  String getSelfId();
  void toJSONString(char* jsonString, size_t length_);
  
}; 

#endif