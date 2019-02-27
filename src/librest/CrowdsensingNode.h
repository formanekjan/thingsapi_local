#ifndef CROWDSENSINGNODE_H
#define CROWDSENSINGNODE_H
#include "ArduinoJson.h"
#include <Arduino.h>
#include "Thing.h"

class CrowdsensingNode : public Thing 
{ 
 private: 

 public:
  CrowdsensingNode(String serialNumber);
  
}; 

#endif