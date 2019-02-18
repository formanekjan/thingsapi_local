#include "Sensor.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Sensor::Sensor(String name_, String description, String encodingType, String metadata) {
  this->name_ = name_;
  this->description = description;
  this->encodingType = encodingType;
  this->metadata = metadata;
}

void Sensor::setSelfId(String selfId) {
  this->selfId = selfId;
}

String Sensor::getSelfId() {
  return selfId;
}

void Sensor::toJSONString(char* jsonString, size_t length_) {
  Serial.print("Create JSON");
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts

  root["name"] = name_;
  root["description"] = description;
  root["encodingType"] = encodingType;
  root["metadata"] = metadata;
  root["@iot.id"] = selfId;
  root.printTo(jsonString, length_);

  
}
