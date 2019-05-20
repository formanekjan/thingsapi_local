#include "FirmwareProperty.h"

/*architektor verkackt, toJSONString muss dieses Objekt eigentlich genau abbilden. Bequemlichkeitshalber wurde aber hier das äußere Properties-Objekt definiert. Muss eigentlich 
in der Aufrufenden klasse, die ein Properties-Objekt enthält erzeugt werden. Beim Patchen gibt es aber keine äußere aufrufende Klasse*/

FirmwareProperty::FirmwareProperty() {
  
}

FirmwareProperty::FirmwareProperty(String date, String version) {
  this->date = date;
  this->version = version;
}

void FirmwareProperty::toJSONObject(JsonObject& root) {
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& firmwareObject = jsonBuffer.createObject(); 
	
	//slightly different structore here than usual, cause date (key) itsels is varying
  firmwareObject[date] = version;	
  root["FW_VERSION"] = firmwareObject;
	
}


void FirmwareProperty::toJSONString(char* jsonString, size_t length_) {
  Serial.print("License Property: Create JSON String");
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  JsonObject& propertyObject = jsonBuffer.createObject(); 
  toJSONObject(propertyObject);
  root["properties"] = propertyObject;
	
  root.printTo(jsonString, length_);
}