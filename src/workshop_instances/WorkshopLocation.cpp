#include "WorkshopLocation.h"
#include "ArduinoJson.h"
#include <Arduino.h>

WorkshopLocation::WorkshopLocation(String name_, float* location) {
  this->name_ = name_;
  this->location[0] = location[0];
  this->location[1] = location[1];
  this->selfId = "geo:"+String(location[0])+","+String(location[1]);
  this->description = "";
  this->encodingType = "application/vnd.geo+json";
}



