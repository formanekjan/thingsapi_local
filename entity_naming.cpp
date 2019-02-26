#ifndef ENTITY_NAMING_H
#define ENTITY_NAMING_H
#include <Arduino.h>

namespace teco {
  //berücksichtigen, ob seriennummern von sensor bekannt oder nicht.
  /*namespace productive
  {
    namespace thing {
      String primer = "saqn:t";
      String operator_url = "teco.edu";
      String human_readable_device_name = "dust_sensor";
      String serial_number = ""; //MAC address
    
      const char* CONTENT_TYPE = "not_set";  //application/json
    }
   
  }*/
  
  namespace development
  {
    namespace thing {
      String primer = "saqn:t:dev";
      String operator_url = "teco.edu";
      String human_readable_device_name = "";
      String serial_number = ""; //MAC address
    }
    namespace sensor {
      String primer = "saqn:s:dev";
      String operator_url = "teco.edu";
      String human_readable_device_name = "";
      String serial_number = ""; //MAC address
    }
    namespace datastream {
      String primer = "saqn:ds:dev";
      String operator_url = "teco.edu";
      String sensor_name = "";
      String serial_number = ""; //MAC address
    }
    
  }
}


#endif
