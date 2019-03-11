#include "ObservedProperty_humidity.h"
#include "EntityNaming.h"
#include "../librest/FrostUtilities.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_Humidity::ObservedProperty_Humidity() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = FROSTEntities::ObservedProperty::preambula+":"+toHEXSHA1("hur").substring(0,7);
}
