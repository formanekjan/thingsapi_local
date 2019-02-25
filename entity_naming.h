#ifndef ENTITY_NAMING_H
#define ENTITY_NAMING_H
#include <Arduino.h>

namespace teco {
  //berücksichtigen, ob seriennummern von sensor bekannt oder nicht.
  namespace productive
  {
    namespace thing {
      extern String primer;
      extern String operator_url;
      extern String human_readable_device_name;
      extern String serial_number; //MAC address
    
      
    }
   
  }
  
  namespace development
  {
    namespace thing {
      extern String primer;
      extern String operator_url;
      extern String human_readable_device_name;
      extern String serial_number; //MAC address
    
    }
  }
}


#endif
