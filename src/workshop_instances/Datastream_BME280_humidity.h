#ifndef DATASTREAM_BME280_HUMIDITY_H
#define DATASTREAM_BME280_HUMIDITY_H

#include "../librest/Datastream.h"
#include <Arduino.h>

class Datastream_Humidity : public Datastream
{ 
 private: 
  
 public:
	Datastream_Humidity(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty);
  Datastream_Humidity(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId);
  
  
}; 

#endif