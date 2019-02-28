#include "ObservedProperty_humidity.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_Humidity::ObservedProperty_Humidity() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = "saqn:op:hur";
}
