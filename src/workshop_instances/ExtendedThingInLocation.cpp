#include "ExtendedThingInLocation.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ExtendedThingInLocation::ExtendedThingInLocation() {
  
}

ExtendedThingInLocation::ExtendedThingInLocation(String name_, String description, String serialNumber) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
}

ExtendedThingInLocation::ExtendedThingInLocation(String name_, String description, String serialNumber, String selfId) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
  this->selfId = selfId;
}

void ExtendedThingInLocation::addLocation(Location* location) {
  this->location = location;
}


void ExtendedThingInLocation::toJSONObject(JsonObject& root) {
 Serial.print("ExtendedThingInLocation: Create JSONObject");
  StaticJsonBuffer<2048> jsonBuffer;
  
  root["name"] = name_;
  root["description"] = description;
  root["@iot.id"] = selfId;

  
  JsonObject& locationObject = jsonBuffer.createObject();
  this->location->toJSONObject(locationObject);
  


  JsonArray* locationArray = NULL;
  locationArray = &jsonBuffer.createArray();
  locationArray->add(locationObject);

  root["Locations"] = *locationArray;
  
  
}

//location not yet implemented
void ExtendedThingInLocation::toJSONString(char* jsonString, size_t length_) {
 Serial.print("ExtendedThingInLocation: Create JSON String");
  StaticJsonBuffer<2048> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  toJSONObject(root);
  root.printTo(jsonString, length_);
}




  


