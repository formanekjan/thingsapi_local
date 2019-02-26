#include "frostID.h"
#include "entity_naming.h"
#include <Arduino.h>

using namespace teco::development;


frostID::frostID() {
 
}

void frostID::addThing(Thing* thing) {
 this->thing = thing;
}

frostID::Thing::Thing(String _name, String commissioning_date, String serialNumber) {
  this->_name = _name;
  this->serialNumber = serialNumber;
  this->commissioning_date = commissioning_date;
  composeId();
}

frostID::Thing::Thing() {
  //create it
}

String frostID::Thing::getId() {
  return this->id;
}

void frostID::Thing::composeId() {
  this->id = thing::primer+":"+thing::operator_url+":"+thing::human_readable_device_name+":"+
              this->commissioning_date+":"+serialNumber;
}

frostID::Sensor::Sensor(String _name, String serialNumber) {
  this->_name = _name;
  this->serialNumber = serialNumber;
  //composeId();
}



