#ifndef DATASTREAM_DHT22_TEMPERATURE_H
#define DATASTREAM_DHT22_TEMPERATURE_H

#include "../librest/Datastream.h"
#include <Arduino.h>

class Datastream_Temperature_DHT22 : public Datastream
{ 
 private: 
  
 public:
	Datastream_Temperature_DHT22(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty);
  Datastream_Temperature_DHT22(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId);
  
  
}; 

#endif