#include "ArduinoJson.h"
#include <HTTPClient.h>
void postThing(HardwareSerial& hwStream) {
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["sensor"] = "gps";
  root["time"] = 1351824120;
  char output[128];
  root.printTo(output);
  /*char root[] =      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";*/
  StaticJsonBuffer<200> jsonBufferParse;
  JsonObject& parsedJSON = jsonBufferParse.parseObject(output);
  const char* sensor = parsedJSON["sensor"];
  long time_ = parsedJSON["time"];
  
  hwStream.println("Print created json");
  hwStream.println("sensor: "+String(sensor));
  hwStream.println("sensor: "+String(time_));
}

void appendHTTPBody(HTTPClient* httpclient) {
  
}

