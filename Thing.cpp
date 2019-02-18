#include "Thing.h"
#include "ArduinoJson.h"
#include <Arduino.h>

/*Thing::Thing() {
  
}*/

Thing::Thing(String name_, String description, String serialNumber) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
}

Thing::Thing(String name_, String description, String serialNumber, float location[]) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
  this->location = location;
}


void Thing::setLocation(float location[]) {
  this->location = location;
}

//location not yet implemented
void Thing::toJSONString(char* jsonString, size_t length_) {
  Serial.print("Create JSON");
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  //alle bezeichner zentral verwalten in einem header
  root["name"] = name_;
  root["description"] = description;
  root["@iot.id"] = serialNumber;
  //Serial.print("Char buffer size: "+String(sizeof(jsonString) / sizeof(jsonString[0])));
  //root.printTo(jsonString, sizeof(jsonString) / sizeof(jsonString[0]));
  root.printTo(jsonString, length_);
}

  


