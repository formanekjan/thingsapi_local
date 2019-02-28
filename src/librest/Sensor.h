#ifndef SENSOR
#define SENSOR

#include <Arduino.h>

class Sensor
{ 
 protected: 
  String name_;
  String description;
  String encodingType;
  String metadata;
	String serialNumber;
  String selfId;
  
 public:
	Sensor();
  Sensor(String name_, String description, String encodingType, String metadata, String serialNumber);
  void setSelfId(String selfId);
  String getSelfId();
	String getSerialNumber();
  void toJSONString(char* jsonString, size_t length_);
  
}; 

#endif