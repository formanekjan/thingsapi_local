class Thing 
{ 
 private: 
  char* name_; 
  char* description; 
  float* location;
  char* serialNumber; 
 public:
  Thing();  
  Thing(char* name_, char* description, float location[], char* serialNumber);
  Thing(char* name_, float location[], char* serialNumber); 
  void toJSON();
  void setLocation(float location[]);
}; 
