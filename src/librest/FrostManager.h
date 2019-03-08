#ifndef FROST_MANAGER_H
#define FROST_MANAGER_H

#include "Datastream.h"
#include "Observation.h"
#include "ToJSONString.h"
#include <Arduino.h>


class FrostManager
{ 
	public:
		enum UsedSensor {
				BME280 = 0,
				DHT22 = 1,
		};
	
	private: 
		String device_Serial;
		String SDS011_Serial;
		String BME280_Serial;
		float location[3];
		String humanReadableLocation;
		String usedSensorSerial;
		
	public:
		String dataStreamPM10_Id;
		String dataStreamPM2_5Id;
		String dataStreamTemperatureBME280_Id;
		String dataStreamHumidityBME280_Id;
		String dataStreamPressureBME280_Id;
		String dataStreamTemperatureDHT22_Id;
		String dataStreamHumidityDHT22_Id;
		UsedSensor usedSensor;
		
	
  
	public:
		FrostManager();
		FrostManager(String device_Serial, String SDS011Serial, UsedSensor usedSensor, String usedSensorSerial, float* location, String humanReadableLocation);
		void createEntities();
		void postObservation(Observation* observation);
	
	private:
		int createThing();
		int createBME280();
		int createSDS011();
		int createObsPropPM10();
		int createObsPropPM2_5();
		int createObsPropTemperature();
		int createObsPropHumidity();
		int createObsPropPressure();
		int createEntity(String url, ToJSONString* toJSONString);
		
  
  
}; 

#endif
