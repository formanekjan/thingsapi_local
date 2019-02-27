#include "CrowdsensingNode.h"
#include "ArduinoJson.h"
#include <Arduino.h>


CrowdsensingNode::CrowdsensingNode(String serialNumber) {
  this->serialNumber = serialNumber;
  this->name_ = "Crowdsensing Node (SDS011, "+serialNumber+")";
  this->description = "Low Cost Node Measuring Particulate Matter";
  this->selfId = "saqn:t:teco.edu:crowdsensor:2019-03:"+serialNumber;
  
}


void CrowdsensingNode::toJSONString(char* jsonString, size_t length_) {
  //use own implementation, if base class implementation isn't adequate
  
  ThingInLocation::toJSONString(jsonString, length_);
}

  


