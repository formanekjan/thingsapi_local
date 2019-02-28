#include "Datastream_BME280_humidity.h"
#include "ArduinoJson.h"
#include <Arduino.h>

Datastream_Humidity::Datastream_Humidity(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty): 
	Datastream_Humidity(thing->getSelfId(), thing->getSerialNumber(), sensor->getSelfId(), sensor->getSerialNumber(), observedProperty->getSelfId()) {
	Serial.println("Datastream constructor 1");
	Serial.println("Thing pointer: ");
	Serial.println((int)thing);
	Serial.println(thing->getSerialNumber());
	this->thing = thing;
	this->sensor = sensor;
	this->observedProperty = observedProperty;
	//Datastream_Humidity(thing->getSelfId(), sensor->getSelfId());
  //Datastream_Humidity("lalala", "abcde");
}

Datastream_Humidity::Datastream_Humidity(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId) {
	Serial.println("Datastream constructor 2");
	Serial.println(deviceSerial);
	this->thingId = thingId;
	this->sensorId = sensorId;
	this->observedPropertyId = observedPropertyId;
  this->name_ = "Relative Humidity Datastream of Crowdsensing Node (SDS011,"+deviceSerial+")";
  this->description = "Datastream for recording relative humidity";
  this->unitOfMeasurement.name_ = "Degree Celsius";
	this->unitOfMeasurement.symbol = "degC";
	this->unitOfMeasurement.definition = "http://cfconventions.org/Data/cf-standard-names/63/build/cf-standard-name-table.html";
  this->observationType = "http://www.opengis.net/def/observationType/OGC-OM/2.0/OM_Measurement";
	this->selfId = "saqn:ds:teco.edu:bme280:"+sensorSerial+"_"+deviceSerial+":ta";
	
	
	
}

