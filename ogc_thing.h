#ifndef OGC_THING_H
#define OGC_THING_H

namespace OGC_thing
{
  const char* primer = "saqn:t";
  const char* model = "not_set";
  const char* serial_number = "not_set";

  const char* CONTENT_TYPE = "not_set";  //application/json
}

void postThing(HardwareSerial& hwStream); //bare thing with everything on default parameters
//void postThing(const char* serverURL);
void appendHTTPBody(HTTPClient* httpclient);
void appendHTTPHeader(HTTPClient* httpclient);

#endif
