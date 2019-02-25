#include <Arduino.h>
#include "ArduinoJson.h"

class Datastream 
{ 
 private: 
  String name_; 
  String description; 
  String observationType;
  String selfId; 
  String sensorId;
  String thingId;
  String observedPropertyId;
  bool locationIdSet = false;
  class UnitOfMeasurement {
    public:
      String name_;
      String symbol;
      String definition;
      void toJSONObject(JsonObject& jsonObject);
  };
  UnitOfMeasurement unitOfMeasurement;
 public:
   
  Datastream(String name_, String description, String observationType);
  void setSelfId(String selfId);
  void setSensorId(String sensorId);
  void setThingId(String thingId);
  void setObservedPropertyId(String observedPropertyId);
  void setUnitOfMeasurement(String name_, String description, String definition);
  void toJSONString(char* jsonString, size_t length_);
  
    
    
  
  
}; 
