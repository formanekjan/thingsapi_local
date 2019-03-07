#include "Sensor_DHT22.h"
#include "ArduinoJson.h"
#include <Arduino.h>

DHT22_Sensor::DHT22_Sensor(String serialNumber) {
  this->name_ = "DHT22";
  this->description = "A sensor measuring temperature and humidity";
  this->encodingType = "application/pdf";
  this->metadata = "https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf";
	this->selfId = "saqn:s:teco.edu:dht22";
	this->serialNumber = serialNumber;
}
