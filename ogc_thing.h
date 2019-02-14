#ifndef OGC_THING_H
#define OGC_THING_H

namespace OGC_thing
{
  const char* primer = "saqn:t";
  const char* model = "not_set";
  const char* serial_number = "not_set";

  const char* CONTENT_TYPE = "not_set";  //application/json
}


String createID(String serialNumber);
// createJSON();
void appendHTTPBody(HTTPClient* httpclient);
void appendHTTPHeader(HTTPClient* httpclient);

#endif
