#include "Thing.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Thing::Thing() {
  
}
Thing::Thing(String name_, String description, String serialNumber) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
}

Thing::Thing(String name_, String description, String serialNumber, String selfId) {
  this->name_ = name_;
  this->description = description;
  this->serialNumber = serialNumber;
  this->selfId = selfId;
}



void Thing::setLocationId(String locationId) {
  this->locationId = locationId;
  locationIdSet = true;
  
}

void Thing::toJSONObject(JsonObject& root) {
	//alle bezeichner zentral verwalten in einem header
	StaticJsonBuffer<2048> jsonBuffer; //inner buffer shouldnt exceed outer buffer
	root["name"] = name_;
	root["description"] = description;
	root["@iot.id"] = selfId;

	if(locationIdSet) {
		JsonObject& locationObject = jsonBuffer.createObject();
		locationObject["@iot.id"] = locationId;

		JsonArray* locationArray = NULL;
		locationArray = &jsonBuffer.createArray();
		locationArray->add(locationObject);

		root["Locations"] = *locationArray;
	}
}
	

	
//location not yet implemented
void Thing::toJSONString(char* jsonString, size_t length_) {
  Serial.print("Thing: Create JSON String");
  StaticJsonBuffer<2048> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  toJSONObject(root);
  root.printTo(jsonString, length_);
	
}

String Thing::getSelfId() {
	return selfId;
}

String Thing::getSerialNumber() {
	return serialNumber;
}
  


