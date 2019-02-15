#include "Thing.h"
#include "ArduinoJson.h"
#include <Arduino.h>

/*Thing::Thing() {
  
}*/

Thing::Thing(char* name_, char* description, char* serialNumber) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
}

Thing::Thing(char* name_, char* description, char* serialNumber, float location[]) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
  this->location = location;
}


void Thing::setLocation(float location[]) {
  this->location = location;
}

//location not yet implemented
void Thing::toJSONString(char* jsonString) {
  Serial.print("Create JSON");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  //alle bezeichner zentral verwalten in einem header
  root["name"] = name_;
  root["description"] = description;
  root["@iot.id"] = serialNumber;
  root.printTo(jsonString, sizeof(jsonString) / sizeof(jsonString[0]));
  
}

  


