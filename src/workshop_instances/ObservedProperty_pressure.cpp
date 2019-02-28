#include "ObservedProperty_pressure.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_Pressure::ObservedProperty_Pressure() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = "saqn:op:plev";
}
