#include "Sensor_BME280.h"
#include "ArduinoJson.h"
#include <Arduino.h>

BME280_Sensor::BME280_Sensor() {
  this->name_ = "Bosch BME280";
  this->description = "A sensor measuring temperature, atmospheric pressure and humidity";
  this->encodingType = "application/pdf";
  this->metadata = "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf";
	this->selfId = "saqn:s:teco.edu:bme280";
}
