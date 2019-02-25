#include "frost_id_creator.h"
#include "entity_naming.h"
#include <Arduino.h>

using namespace teco::development::thing;

//String delimiter = "/";
IdSet::IdSet(String MAC, String sensorIds[], int sensorIdLength) {
  this->MAC = MAC;
  this->sensors = new String[sensorIdLength];
  //copy array
  for(int i=0; i<sensorIdLength; i++) {
    sensors[i] = sensorIds[i];
  }
  
}

void IdSet::createThingId() {
  //this->thingId = primer+"/"+operator_url+"/"+human_readable_device_name+"/"+
}




