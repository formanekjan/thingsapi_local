#include "FrostManager.h"
#include "Frost_Server.h"
#include "../workshop_instances/workshop_entities.h"
#include "ArduinoJson.h"
#include <Arduino.h>
#include <HTTPClient.h>


FrostManager::FrostManager() {
  
}

FrostManager::FrostManager(String device_Serial, String SDS011_Serial, String BME280_Serial, float* location, String humanReadableLocation) {
	this->device_Serial = device_Serial;
	this->SDS011_Serial = SDS011_Serial;
	this->BME280_Serial = BME280_Serial;
	this->location[0] = location[0];
	this->location[1] = location[1];
	this->location[2] = location[2];
	this->humanReadableLocation = humanReadableLocation;
	
}

int FrostManager::createThing() {
	
	return 0;
}

int createBME280() {
	return 0;
}

int createSDS011() {
	return 0;
}


int createObsPropPM10() {
	return 0;
}


int createObsPropPM2_5() {
	return 0;
}

int createObsPropTemperature() {
	return 0;
}


int createObsPropHumidity() {
	return 0;
}


int createObsPropPressure() {
	return 0;
}

int FrostManager::createEntity(String url, ToJSONString* toJSONString) { //it would have also been possible to pass a string reference as second parameter
	
		HTTPClient http;
		char jsonbuffer[2048];
    size_t j = sizeof(jsonbuffer) / sizeof(jsonbuffer[0]);
		int httpCode;
		Serial.print("URL");
		Serial.print(url);
		Serial.print("JSON_buffer");
		toJSONString->toJSONString(jsonbuffer, j);
		Serial.print(jsonbuffer);
		http.begin(url);
    http.addHeader("Content-Type", "application/json");
		
    httpCode = http.POST(jsonbuffer);
    if(httpCode < 0) {
    Serial.println("Error on HTTP post");
    Serial.println("Code "+String(httpCode));
    }
    else {
    Serial.println("HTTP Code: "+String(httpCode));
    }
    http.end();
		return httpCode;
}


void FrostManager::createEntities() {
	
	WorkshopLocationEntry myWorkshopLocationEntry(location);
	WorkshopLocation myWorkshopLocation(humanReadableLocation, &myWorkshopLocationEntry);

	CrowdsensingNode myCrowdsensingNode(device_Serial); //Thing
	myCrowdsensingNode.addLocation(&myWorkshopLocation);
	
	

	createEntity(FROST_Server::things_url, &myCrowdsensingNode);
	
	BME280_Sensor mybme280Sensor(BME280_Serial);
	createEntity(FROST_Server::sensors_url, &mybme280Sensor);
	
	SDS011_Sensor mySDS011Sensor(SDS011_Serial);
	createEntity(FROST_Server::sensors_url, &mySDS011Sensor);

	ObservedProperty_PM2_5 property_pm2_5;
	createEntity(FROST_Server::observedproperties_url, &property_pm2_5);
	
	Datastream_PM2_5 datastream_pm2_5(&myCrowdsensingNode, &mySDS011Sensor, &property_pm2_5);
	this->dataStreamPM2_5Id = datastream_pm2_5.getSelfId();
	createEntity(FROST_Server::datastreams_url, &datastream_pm2_5);
	
	ObservedProperty_PM10 property_pm10;
	createEntity(FROST_Server::observedproperties_url, &property_pm10);
	
	Datastream_PM10 datastream_pm10(&myCrowdsensingNode, &mySDS011Sensor, &property_pm10);
	this->dataStreamPM10_Id = datastream_pm10.getSelfId();
	createEntity(FROST_Server::datastreams_url, &datastream_pm10);

	ObservedProperty_Humidity property_Humidity;
	createEntity(FROST_Server::observedproperties_url, &property_Humidity);
	
	Datastream_Humidity datastream_Humidity(&myCrowdsensingNode, &mybme280Sensor, &property_Humidity);
	this->dataStreamHumidity_Id = datastream_Humidity.getSelfId();
	createEntity(FROST_Server::datastreams_url, &datastream_Humidity);

	ObservedProperty_Pressure property_Pressure;
	createEntity(FROST_Server::observedproperties_url, &property_Pressure);
	
	Datastream_Pressure datastream_Pressure(&myCrowdsensingNode, &mybme280Sensor, &property_Pressure);
	this->dataStreamPressure_Id = datastream_Pressure.getSelfId();
	createEntity(FROST_Server::datastreams_url, &datastream_Pressure);

	ObservedProperty_Temperature property_Temperature;
	createEntity(FROST_Server::observedproperties_url, &property_Temperature);
	
	Datastream_Temperature datastream_Temperature(&myCrowdsensingNode, &mybme280Sensor, &property_Temperature);
	this->dataStreamTemperature_Id = datastream_Temperature.getSelfId();
	createEntity(FROST_Server::datastreams_url, &datastream_Temperature);
	
}


