#ifndef DATASTREAM_BME280_TEMPERATURE_H
#define DATASTREAM_BME280_TEMPERATURE_H

#include "../librest/Datastream.h"
#include <Arduino.h>

class Datastream_Temperature : public Datastream
{ 
 private: 
  
 public:
	Datastream_Temperature(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty);
  Datastream_Temperature(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId);
  
  
}; 

#endif