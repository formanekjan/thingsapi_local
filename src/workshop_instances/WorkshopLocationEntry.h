#ifndef WORKSHOPLOCATIONENTRY_H
#define WORKSHOPLOCATIONENTRY_H
#include "ArduinoJson.h"
#include <Arduino.h>
#include "../librest/Location.h"

class WorkshopLocationEntry: public LocationEntry
{ 
 protected:
	float coordinates[3];
	String type;
 public:
  void toJSONObject(JsonObject& root);
	void toJSONString(char* jsonString, size_t length_);
	String getIDRepresentation();
	WorkshopLocationEntry(float* coordinates);
  
  
}; 

#endif
