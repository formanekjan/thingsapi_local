#ifndef LOCATION_ENTRY_H
#define LOCATION_ENTRY_H

#include "ArduinoJson.h"
#include <Arduino.h>

class LocationEntry 
{ 
 public: 
	virtual JsonObject getJSONObject() = 0; 
	LocationEntry();
	~LocationEntry();
  
}; 

#endif