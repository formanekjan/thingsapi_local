#ifndef DATASTREAM
#define DATASTREAM

#include <Arduino.h>
#include "ArduinoJson.h"
#include "Sensor.h"
#include "Thing.h"
#include "ObservedProperty.h"

class Datastream 
{ 
 protected: 
  String name_; 
  String description; 
  String observationType;
  String selfId; 
  String sensorId;
  String thingId;
  String observedPropertyId;
	Sensor* sensor;
	Thing* thing;
	ObservedProperty* observedProperty;
	
  class UnitOfMeasurement {
    public:
      String name_;
      String symbol;
      String definition;
      void toJSONObject(JsonObject& jsonObject);
  };
  UnitOfMeasurement unitOfMeasurement;
 public:
  
	Datastream();
  Datastream(String name_, String description, String observationType);
  void setSelfId(String selfId);
  void setSensorId(String sensorId);
  void setThingId(String thingId);
  void setObservedPropertyId(String observedPropertyId);
  void setUnitOfMeasurement(String name_, String description, String definition);
  void toJSONString(char* jsonString, size_t length_);
	String getSelfId();
  
    
    
  
  
}; 

#endif
