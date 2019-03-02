#ifndef FROST_MANAGER_H
#define FROST_MANAGER_H

#include "Datastream.h"
#include "ToJSONString.h"
#include <Arduino.h>


class FrostManager
{ 
	private: 
		String device_Serial;
		String SDS011_Serial;
		String BME280_Serial;
		float location[3];
		String humanReadableLocation;
		
		String dataStreamPM10_Id;
		String dataStreamPM2_5Id;
		String dataStreamTemperature_Id;
		String dataStreamHumidity_Id;
		String dataStreamPressure_Id;
	
  
	public:
		FrostManager();
		FrostManager(String device_Serial, String SDS011Serial, String BME280_Serial, float* location, String humanReadableLocation);
		void createEntities();
	
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
