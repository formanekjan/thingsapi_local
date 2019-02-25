#include "Observation.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Observation::Observation(String phenomenonTime, double result, String resultTime) {
  this->phenomenonTime = phenomenonTime;
  this->result = result;
  this->resultTime = resultTime;
}

void Observation::setSelfId(String selfId) {
  this->selfId = selfId;
}



void Observation::toJSONString(char* jsonString, size_t length_) {
  /*Serial.print("Create JSON");
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts

  root["name"] = name_;
  root["description"] = description;
  root["definition"] = definition;
  root["@iot.id"] = selfId;
  
  root.printTo(jsonString, length_);*/

  
}
