#ifndef LICENSED_DATASTREAM_H
#define LICENSED_DATASTREAM_H

#include "../librest/Datastream.h"
#include "LicenseProperty.h"

class LicensedDatastream : public Datastream, public ToJSONString
{ 
 protected: 
	LicenseProperty licenseProperty;
	
  
 public:
  LicensedDatastream();
  //LicensedDatastream(String name_, String description, String observationType);
  void setLicenseProperty(LicenseProperty licenseProperty);
  void ToJSONString(); //muss überschrieben werden, weil Lizenz mit aufgeführt wird
}; 

#endif
