/*This class is intended to generate IDs for all FROST-Entities with only 
a MAC-Adress of a LAN-Module and the Serials for each Sensor*/

#ifndef FROST_ID_CREATOR_H
#define FROST_ID_CREATOR_H

#include <Arduino.h>

class IdSet
{
  public:
    String dataStreamId;
    String featureOfInterestId;
    String locationId;
    String observationId;
    String observedPropertyId;
    String sensorId;
    String thingId;

    String MAC;
    String* sensors;

    IdSet(String MAC, String sensorIds[], int sensorIdLength);
    void createThingId();
    
};

#endif
