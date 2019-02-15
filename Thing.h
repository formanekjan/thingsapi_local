class Thing 
{ 
 private: 
  char* name_; 
  char* description; 
  float* location;
  char* serialNumber; 
  bool locationSet = false;
 public:
  //Thing();  
  Thing(char* name_, char* description, char* serialNumber);
  Thing(char* name_, char* description, char* serialNumber, float location[]);
  void setLocation(float location[]);
  void toJSONString(char* jsonString);
  
}; 
