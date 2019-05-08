
#include "ExtendedDatastream.h"

ExtendedDatastream::ExtendedDatastream() {
 
}

ExtendedDatastream::ExtendedDatastream(String name_, String description, String observationType): 
	Datastream(name_, description, observationType) {
	this->propertySet = false;
}



//sets, resepectiveley resets property 
void ExtendedDatastream::setProperty(ToJSONObject* property){
	
	this->propertySet = true;
}

void ExtendedDatastream::toJSONObject(JsonObject& root){
	
	
}

void ExtendedDatastream::ToJSONString(char* jsonString, size_t length_){
	Serial.print("Datastream: Create JSON String");
	StaticJsonBuffer<3072> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
	toJSONObject(root);
 
}

