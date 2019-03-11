#include "ObservedProperty_PM2_5.h"
#include "EntityNaming.h"
#include "../librest/FrostUtilities.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_PM2_5::ObservedProperty_PM2_5() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = FROSTEntities::ObservedProperty::preambula+":"+toHEXSHA1("pm2p5").substring(0,7);
}
