#include "frostID.h"
#include "entity_naming.h"
#include <Arduino.h>

//using namespace teco::development::thing;


frostID::frostID() {
 
}

void frostID::addThing(Thing* thing) {
 this->thing = thing;
}

frostID::Thing::Thing(String _name, String ID) {
  this->_name = _name;
  this->id = id;
}

frostID::Thing::Thing() {

}




