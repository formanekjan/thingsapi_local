/*This class is intended to generate IDs for all FROST-Entities with only 
a MAC-Adress of a LAN-Module and the Serials for each Sensor*/

#ifndef FROSTID_H
#define FROSTID_H

#include <Arduino.h>

class frostID
{
    
    public:
      class Thing {
        private:
          String _name;
          String serialNumber;
          String id;
          String commissioning_date;
          void composeId();
        public:
          String getId();
          String getName();
          Thing();
          Thing(String _name, String serialNumber, String commissioning_date);
      };
      
      class Sensor {
        private:
          String _name;
          String serialNumber;
          String id;
        public:
          String getId();
          String getName();
          //Sensor();
          Sensor(String _name, String serialNumber);
      };
  
      class Location {
        public:
          float* location;
      };
  
      class Datastream {
        public:
          Sensor* sensor;
          Thing* thing;
          String getId();
      };
  
      class FeatureOfInterest {
        public:
          String getId();
      };

      class ObservedProperty {
        public:
          String _name;
          String getId();
      };
      
      class Observation {
        public:
          Datastream* datastream;
          String getId(String phenomenonTime);
      };

    public:
      Thing* thing;
      float location[3];
      Sensor* sensor[5];
      Datastream* datastream[20];
      ObservedProperty* observerdProperty[20]; //so that each datastream can have a different observerd property
      Observation* observation[20];
      FeatureOfInterest* featureOfInterest[20];
  
       //global vars vor all sub objects
      String operatorURL;
      
      void addThing(Thing* thing);
      void addSensor(Sensor* sensor);
      void addLocation(float* location);
      void addDatastream(Thing* thing, Sensor* sensor);
      void addFeatureOfInterest(FeatureOfInterest* featureOfInterest);
      void addObserverdProperty(ObservedProperty* observedProperty);
      void addObservation(Datastream* datastream);
      
      frostID();

    
};

#endif
