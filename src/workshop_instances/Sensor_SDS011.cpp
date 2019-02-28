#include "Sensor_SDS011.h"
#include "ArduinoJson.h"
#include <Arduino.h>

SDS011_Sensor::SDS011_Sensor(String serialNumber) {
  this->name_ = "Nova SDS011";
  this->description = "A low-cost sensor measuring particulate matter";
  this->encodingType = "application/pdf";
  this->metadata = "https://www.watterott.com/media/files_public/fwyjbmbnj/SDS011.pdf";
	this->selfId = "saqn:s:teco.edu:sds011";
	this->serialNumber = serialNumber;
}
