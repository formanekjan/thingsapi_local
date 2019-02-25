#ifndef OBSERVATION
#define OBSERVATION

#include <Arduino.h>

class Observation
{ 
 private: 
  String phenomenonTime;
  double result; //subclass and overwrite if other result type is neccessary
  String resultTime;
 
  String selfId;
  String featureOfInterestId;
  String datastreamId;
  
 public:
  Observation(String phenomenonTime, double result, String resultTime);
  void setSelfId(String selfId);
  void setFeatureOfInterestId(String featureOfInterestId);
  void setDatastreamId(String datastreamId);
  void toJSONString(char* jsonString, size_t length_);
  
}; 

#endif
