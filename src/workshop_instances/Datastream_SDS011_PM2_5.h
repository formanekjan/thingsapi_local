#ifndef DATASTREAM_SDS011_PM2_5_H
#define DATASTREAM_SDS011_PM2_5_H

#include "../librest/Datastream.h"
#include <Arduino.h>

class Datastream_PM2_5 : public Datastream
{ 
 private: 
  
 public:
	Datastream_PM2_5(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty);
  Datastream_PM2_5(String thingId, String deviceSerial, String sensorId, String observedPropertyId);
  
  
}; 

#endif