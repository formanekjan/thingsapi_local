#include "ObservedProperty_pressure.h"
#include "EntityNaming.h"
#include "../librest/FrostUtilities.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_Pressure::ObservedProperty_Pressure() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = FROSTEntities::ObservedProperty::preambula+":"+toHEXSHA1("plev").substring(0,7);
}
