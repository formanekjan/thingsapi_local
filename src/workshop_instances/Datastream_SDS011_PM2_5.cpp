#include "Datastream_SDS011_PM2_5.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Datastream_PM2_5::Datastream_PM2_5(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty): 
	Datastream_PM2_5(thing->getSelfId(), thing->getSerialNumber(), sensor->getSelfId(), sensor->getSerialNumber(), observedProperty->getSelfId()) {
	Serial.println("Datastream constructor 1");
	Serial.println("Thing pointer: ");
	Serial.println((int)thing);
	Serial.println(thing->getSerialNumber());
	this->thing = thing;
	this->sensor = sensor;
	this->observedProperty = observedProperty;
	//Datastream_PM2_5(thing->getSelfId(), sensor->getSelfId());
  //Datastream_PM2_5("lalala", "abcde");
}

Datastream_PM2_5::Datastream_PM2_5(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId) {
	Serial.println("Datastream constructor 2");
	Serial.println(deviceSerial);
	this->thingId = thingId;
	this->sensorId = sensorId;
	this->observedPropertyId = observedPropertyId;
  this->name_ = "PM2.5 Datastream  of Crowdsensing Node (SDS011, "+deviceSerial+")";
  this->description = "A low-cost sensor measuring particulate matter";
  this->unitOfMeasurement.name_ = "microgram per cubic meter";
	this->unitOfMeasurement.symbol = "ug/m^3";
	this->unitOfMeasurement.definition = "http://cfconventions.org/Data/cf-standard-names/63/build/cf-standard-name-table.html";
  this->observationType = "http://www.opengis.net/def/observationType/OGC-OM/2.0/OM_Measurement";
	this->selfId = "saqn:ds:teco.edu:sds011"+sensorSerial+"_"+deviceSerial+":pm2p5";
	
	
	//this->selfId = "saqn:s:teco.edu:sds011";
}

