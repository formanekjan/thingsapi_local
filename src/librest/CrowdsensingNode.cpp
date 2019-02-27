#include "CrowdsensingNode.h"
#include "ArduinoJson.h"
#include <Arduino.h>

/*Thing::Thing() {
  
}*/

CrowdsensingNode::CrowdsensingNode(String serialNumber) {
  this->serialNumber = serialNumber;
  this->name_ = "Crowdsensing Node (SDS011, "+serialNumber+")";
  this->description = "Low Cost Node Measuring Particulate Matter";
  this->selfId = "saqn:t:teco.edu:crowdsensor:2019-03:"+serialNumber;
  
}


/*void CrowdsensingNode::setLocationId(String locationId) {
  this->locationId = locationId;
  locationIdSet = true;
  
}

//location not yet implemented
void CrowdsensingNode::toJSONString(char* jsonString, size_t length_) {
  Serial.print("Create JSON");
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  //alle bezeichner zentral verwalten in einem header
  root["name"] = name_;
  root["description"] = description;
  root["@iot.id"] = serialNumber;

  if(locationIdSet) {
    JsonObject& locationObject = jsonBuffer.createObject();
    locationObject["@iot.id"] = locationId;
  
    JsonArray* locationArray = NULL;
    locationArray = &jsonBuffer.createArray();
    locationArray->add(locationObject);
    
    root["Locations"] = *locationArray;
  }
  root.printTo(jsonString, length_);
}*/

  


