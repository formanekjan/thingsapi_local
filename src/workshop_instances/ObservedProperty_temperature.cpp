#include "ObservedProperty_temperature.h"
#include "EntityNaming.h"
#include "../librest/FrostUtilities.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_Temperature::ObservedProperty_Temperature() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = FROSTEntities::ObservedProperty::preambula+":"+toHEXSHA1("ta").substring(0,7);

}
