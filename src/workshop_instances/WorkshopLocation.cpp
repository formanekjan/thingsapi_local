#include "WorkshopLocation.h"
#include "ArduinoJson.h"
#include <Arduino.h>

WorkshopLocation::WorkshopLocation(String humanReadableLocation, LocationEntry* locationEntry) {
	
  this->locationEntry = locationEntry;
	this->name_ = humanReadableLocation;
  this->selfId = "geo:"+this->locationEntry->getIDRepresentation();
  this->encodingType = "application/vnd.geo+json";
}



