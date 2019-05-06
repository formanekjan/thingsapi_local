#ifndef License_Property_H
#define License_Property_H

#include "ArduinoJson.h"
#include <Arduino.h>

//Property in Classname indicates, that it shell be only used in the property section of an element

class LicenseProperty 
{ 
 private:
 	String type;
	String owner;
	String metadata;
 public: 
	void toJSONObject(JsonObject& root);
	
  
}; 

#endif