#include "ThingInLocation.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ThingInLocation::ThingInLocation() {
  
}

ThingInLocation::ThingInLocation(String name_, String description, String serialNumber) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
}

ThingInLocation::ThingInLocation(String name_, String description, String serialNumber, String selfId) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
  this->selfId = selfId;
}

void ThingInLocation::addLocation(Location* location) {
  this->location = location;
}


void ThingInLocation::toJSONObject(JsonObject& root) {
 Serial.print("ThingInLocation: Create JSONObject");
  StaticJsonBuffer<2048> jsonBuffer;
  Thing::toJSONObject(root);  //uses things method for creation of the base json entries
	
  JsonObject& locationObject = jsonBuffer.createObject();
  this->location->toJSONObject(locationObject);
  
  JsonArray* locationArray = NULL;
  locationArray = &jsonBuffer.createArray();
  locationArray->add(locationObject);

  root["Locations"] = *locationArray;
  
  
}

//location not yet implemented
void ThingInLocation::toJSONString(char* jsonString, size_t length_) {
 Serial.print("ThingInLocation: Create JSON String");
  StaticJsonBuffer<2048> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  toJSONObject(root);
  root.printTo(jsonString, length_);
}




  


