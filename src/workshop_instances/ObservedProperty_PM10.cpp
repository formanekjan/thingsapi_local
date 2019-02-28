#include "ObservedProperty_PM10.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_PM10::ObservedProperty_PM10() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = "saqn:op:pm10";
}
