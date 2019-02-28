#include "ObservedProperty_temperature.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_Temperature::ObservedProperty_Temperature() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = "saqn:op:ta";
}
