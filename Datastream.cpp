#include "Datastream.h"
#include "ArduinoJson.h"
#include <Arduino.h>

/*Thing::Thing() {
  
}*/

Datastream::Datastream(String name_, String description, String observationType) {
  this->name_ = name_;
  this->description = description;
  this->observationType = observationType;
}


void Datastream::setSelfId(String selfId) {
  this->selfId = selfId;
}

//location not yet implemented
void Datastream::toJSONString(char* jsonString, size_t length_) {

  
  Serial.print("Create JSON");
  StaticJsonBuffer<400> jsonBuffer;
  
  /*
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  //alle bezeichner zentral verwalten in einem header
  root["name"] = name_;
  root["description"] = description;
  root["@iot.id"] = serialNumber;

  if(locationIdSet) {
    JsonObject& locationObject = jsonBuffer.createObject();
    locationObject["@iot.id"] = locationId;
  
    JsonArray* locationArray = NULL;
    locationArray = &jsonBuffer.createArray();
    locationArray->add(locationObject);
    
    root["Locations"] = *locationArray;
  }
  root.printTo(jsonString, length_);*/
}

void Datastream::UnitOfMeasurement::toJSONObject(JsonObject& jsonObject) {
  Serial.print("Create JSON");
  jsonObject["name"] = this->name_;
  jsonObject["symbol"] = this->symbol;
  jsonObject["definition"] = this->definition;
  
}

void Datastream::setUnitOfMeasurement(String name_, String symbol, String definition) {
  this->unitOfMeasurement.name_ = name_; 
  this->unitOfMeasurement.symbol = symbol; 
  this->unitOfMeasurement.definition = definition; 
}


  


