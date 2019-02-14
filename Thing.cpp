#include "Thing.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Thing::Thing() {
  
}

Thing::Thing(char* name_, char* description, float location[], char* serialNumber) {
  this->name_ = name_;
  this->description = description;
  this->location = location;
  this->serialNumber = serialNumber;
}

Thing::Thing(char* name_, float location[], char* serialNumber) {
  this->name_ = name_;
  this->location = location;
  this->serialNumber = serialNumber;
}


void Thing::setLocation(float location[]) {
  this->location = location;
}

void toJSON() {
 
}

