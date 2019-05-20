#include "ExtendedThing.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ExtendedThing::ExtendedThing() {
  
}
ExtendedThing::ExtendedThing(String name_, String description, String serialNumber): 
	Thing(name_, description, serialNumber) {
	this->propertySet = false;
}

ExtendedThing::ExtendedThing(String name_, String description, String serialNumber, String selfId): 
  Thing(name_, description, serialNumber, selfId) {
	this->propertySet = false;
}

//location not yet implemented
void ExtendedThing::toJSONObject(JsonObject& root) {
  Serial.print("ExtendedThing:toJSONObject");
	if(propertySet) {
		Serial.println("ExtendedThing property set");
		StaticJsonBuffer<1024> jsonBuffer;
		JsonObject& propertyObject = jsonBuffer.createObject();
		property->toJSONObject(propertyObject); //generates key-value pairs
		root["properties"] = propertyObject;
	}
	else {
		Serial.println("No ExtendedThing property set");
	}
	Thing::toJSONObject(root);
}

//location not yet implemented
void ExtendedThing::toJSONString(char* jsonString, size_t length_) {
  Serial.print("ExtendedThing: Create JSON String");
	StaticJsonBuffer<3072> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
	toJSONObject(root);
	root.printTo(jsonString, length_);
}




