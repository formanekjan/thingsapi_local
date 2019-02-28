#include "ObservedProperty_PM2_5.h"
#include "ArduinoJson.h"
#include <Arduino.h>

ObservedProperty_PM2_5::ObservedProperty_PM2_5() {
  this->name_ = "";
  this->description = "";
  this->definition = "";
	this->selfId = "saqn:op:pm10";
}
