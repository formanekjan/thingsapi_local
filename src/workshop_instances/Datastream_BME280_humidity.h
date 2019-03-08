#ifndef DATASTREAM_BME280_HUMIDITY_H
#define DATASTREAM_BME280_HUMIDITY_H

#include "../librest/Datastream.h"
#include <Arduino.h>

class DatastreamHumidityBME280 : public Datastream
{ 
 private: 
  
 public:
	DatastreamHumidityBME280(Thing* thing, Sensor* sensor, ObservedProperty* observedProperty);
  DatastreamHumidityBME280(String thingId, String deviceSerial, String sensorId, String sensorSerial, String observedPropertyId);
  
  
}; 

#endif