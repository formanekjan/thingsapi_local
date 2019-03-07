#ifndef DATASTREAM_DHT22_HUMIDITY_H
#define DATASTREAM_DHT22_HUMIDITY_H

#include "../librest/Datastream.h"
#include <Arduino.h>

class Datastream_Humidity_DHT22 : public Datastream
{ 
 private: 
  
 public:
	Datastream_Humidity_DHT22(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty);
  Datastream_Humidity_DHT22(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId);
  
  
}; 

#endif