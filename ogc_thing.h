#ifndef OGC_THING_H
#define OGC_THING_H

namespace OGC_thing
{
  const char* primer = "saqn:t";
  const char* model = "not_set";
  const char* serial_number = "not_set";
}

void postThing(const char* serverURL); //bare thing with everything on default parameters
void postThing(const char* serverURL);


#endif
