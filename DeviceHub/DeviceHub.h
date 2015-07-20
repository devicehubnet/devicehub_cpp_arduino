#ifndef DeviceHub_h
#define DeviceHub_h

#include <uuid/uuid.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <sstream>

#include <Ethernet.h>
#include <PubSubClient.h>
#include <Arduino.h>

using namespace std;

#ifndef _UUID_STRING_T
#define _UUID_STRING_T
typedef char uuid_string_t[37];
#endif

 
#ifndef _UUID_SSTRING_T
#define _UUID_SSTRING_T
typedef char uuid_sstring_t[5];
#endif 

#define TOPIC_SIZE 150
#define PAYLOAD_SIZE 30

typedef uuid_string_t device_uuid_t;
typedef uuid_string_t api_key_t;
typedef uuid_sstring_t project_id_t;

class DeviceHub {
  
  public:
    
    DeviceHub(project_id_t, device_uuid_t, api_key_t, PubSubClient&);
    bool connect(char[]);
    void callback(char[], byte[], unsigned int);
    void autoconfigure();
    
    void sendSensor(char[], long int);
    void addActuator(char[]);
   
   
    void loop();
    void disconnect();
    enum sensorTypes {
        NUMERIC = 0,
        DIGITAL
    };
 
  private:
    PubSubClient* pahoClient;
    api_key_t api_key;
    project_id_t project_id;
    device_uuid_t device_id;
    bool connected;

};

#endif