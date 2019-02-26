//this global variables are intended to create an instance of an Sensor

#include "frost_bme280.h"
#include "entity_naming.h"
#include <Arduino.h>

namespace sensorparameters {
  //berücksichtigen, ob seriennummern von sensor bekannt oder nicht.
  namespace BME280
  {
    String _name = "saqn:t:dev";
    String description = "teco.edu";
    String encodingType = "";
    String metadata = "";
  }
}


