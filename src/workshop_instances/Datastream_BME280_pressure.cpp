#include "Datastream_BME280_pressure.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Datastream_Pressure::Datastream_Pressure(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty): 
	Datastream_Pressure(thing->getSelfId(), thing->getSerialNumber(), sensor->getSelfId(), sensor->getSerialNumber(), observedProperty->getSelfId()) {
	Serial.println("Datastream constructor 1");
	Serial.println("Thing pointer: ");
	Serial.println((int)thing);
	Serial.println(thing->getSerialNumber());
	this->thing = thing;
	this->sensor = sensor;
	this->observedProperty = observedProperty;
	//Datastream_Pressure(thing->getSelfId(), sensor->getSelfId());
  //Datastream_Pressure("lalala", "abcde");
}

Datastream_Pressure::Datastream_Pressure(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId) {
	Serial.println("Datastream constructor 2");
	Serial.println(deviceSerial);
	this->thingId = thingId;
	this->sensorId = sensorId;
	this->observedPropertyId = observedPropertyId;
  this->name_ = "Atmospheric Pressure Datastream of Crowdsensing Node (SDS011,"+deviceSerial+")";
  this->description = "Datastream for recording pressure";
  this->unitOfMeasurement.name_ = "Hectopascal";
	this->unitOfMeasurement.symbol = "hPa";
	this->unitOfMeasurement.definition = "http://cfconventions.org/Data/cf-standard-names/63/build/cf-standard-name-table.html";
  this->observationType = "http://www.opengis.net/def/observationType/OGC-OM/2.0/OM_Measurement";
	this->selfId = "saqn:ds:teco.edu:bme280:"+sensorSerial+"_"+deviceSerial+":plev";
	
	
	
}

