#include "ArduinoJson.h"
#include <HTTPClient.h>
#include <Arduino.h>

/*void postThing(HardwareSerial& hwStream) {
  Serial.print("Hello");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps";
  root["time"] = 1351824120;
  char output[128];
  root.printTo(output);
  char root[] =      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  StaticJsonBuffer<200> jsonBufferParse;
  JsonObject& parsedJSON = jsonBufferParse.parseObject(output);
  const char* sensor = parsedJSON["sensor"];
  long time_ = parsedJSON["time"];
  
  Serial.println("Print created json");
  Serial.println("sensor: "+String(sensor));
  Serial.println("sensor: "+String(time_));
}*/

void postThing(HardwareSerial& hwStream) {
  Serial.print("Create JSON");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); //root object filled with further json obejcts
  //versuche geschachteltes objekt zu erstellen
  //"location": {"coordinates":[-18.1002,65.6856],"type":"Point"}
//locatation key, hatt als value 

  JsonArray& arr = jsonBuffer.createArray();
  JsonObject& obj1 = jsonBuffer.createObject();
  obj1["Name"] = "SDS011";
  JsonObject& obj2 = jsonBuffer.createObject();
  obj2["Type"] = "Fine Dust";

  arr.add(obj1);
  arr.add(obj2);
  root["location"] = arr;
  //root.add("location");
  
  /*root["name"] = "Jans Virtual Testbox";
  root["time"] = 1351824120;*/

  //convert object to json string
  char output[128];
  root.printTo(output);
  
  //char root[] =      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  Serial.print("output");
  Serial.println(output);
  
  StaticJsonBuffer<200> jsonBufferParse;
  JsonObject& parsedJSON = jsonBufferParse.parseObject(output);
  
  JsonArray& myarr = parsedJSON["location"];
  JsonObject& arr0 = myarr[0];
  JsonObject& arr1 = myarr[1];
  
  const char* sensorname = arr0["Name"];
  const char* sensortype = arr1["Type"];
  
   
  Serial.println("Print created json");
  Serial.println("sensor: "+String(sensorname));
  Serial.println("type: "+String(sensortype));
}

void appendHTTPBody(HTTPClient* httpclient) {
  
}

