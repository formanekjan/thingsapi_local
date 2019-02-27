#include "WorkshopLocationEntry.h"
#include "ArduinoJson.h"
#include <Arduino.h>

WorkshopLocationEntry::WorkshopLocationEntry(float* coordinates) {
  this->type = "Point";
  this->coordinates[0] = coordinates[0];
	this->coordinates[1] = coordinates[1];
}



void WorkshopLocationEntry::toJSONObject(JsonObject& root) {
  Serial.print("Create JSON Object");
  StaticJsonBuffer<256> jsonBuffer;
 
  JsonArray* pointArray = NULL;
  pointArray = &jsonBuffer.createArray();
  pointArray->add(coordinates[0]);
  pointArray->add(coordinates[1]);

  root["type"] = type; 
  root["coordinates"] = *pointArray;
  
}

void WorkshopLocationEntry::toJSONString(char* jsonString, size_t length_) {
  StaticJsonBuffer<512> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); 
  toJSONObject(root);
 
  root.printTo(jsonString, length_);

  
}

String WorkshopLocationEntry::getHumanReadableRepresentation() {
  return "";

  
}