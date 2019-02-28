#ifndef DATASTREAM_BME280_PRESSURE_H
#define DATASTREAM_BME280_PRESSURE_H

#include "../librest/Datastream.h"
#include <Arduino.h>

class Datastream_Pressure : public Datastream
{ 
 private: 
  
 public:
	Datastream_Pressure(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty);
  Datastream_Pressure(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId);
  
  
}; 

#endif