#include <Arduino.h>

class Thing 
{ 
 private: 
  String name_; 
  String description; 
  float* location;
  String serialNumber; 
  bool locationSet = false;
 public:
  //Thing();  
  Thing(String name_, String description, String serialNumber);
  Thing(String name_, String description, String serialNumber, float location[]);
  void setLocation(float location[]);
  void toJSONString(char* jsonString, size_t length_);
  
}; 
