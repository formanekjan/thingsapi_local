#ifndef WORKSHOPLOCATION_H
#define WORKSHOPLOCATION_H
#include "ArduinoJson.h"
#include <Arduino.h>
#include "../librest/Location.h"

class WorkshopLocation: public Location
{ 
 protected: 
 public:
  WorkshopLocation(String name_, float* location);
  void toJSONObject(JsonObject& root);
  void toJSONString(char* jsonString, size_t length_);
  
}; 

#endif
