#ifndef THING
#define THING

#include <Arduino.h>

class Thing 
{ 
 protected: 
  String name_; 
  String description; 
  String locationId;
  String serialNumber;
  String selfId; 
  bool locationIdSet = false;
 public:
  Thing();  
  Thing(String name_, String description, String selfId);
  Thing(String name_, String description, String serialNumber, String selfId);
  void setLocationId(String locationId);
  void toJSONString(char* jsonString, size_t length_);
	String getSelfId();
	String getSerialNumber();
  
}; 

#endif