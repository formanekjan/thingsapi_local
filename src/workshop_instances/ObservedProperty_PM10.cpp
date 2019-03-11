#include "ObservedProperty_PM10.h"
#include "EntityNaming.h"
#include "../librest/FrostUtilities.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_PM10::ObservedProperty_PM10() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = FROSTEntities::ObservedProperty::preambula+":"+toHEXSHA1("pm10").substring(0,7);
}
