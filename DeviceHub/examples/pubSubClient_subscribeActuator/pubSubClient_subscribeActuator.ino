#include <Ethernet.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <DeviceHub.h>


byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
//byte server[]   = { 104, 155, 7, 31 };    //server ip ( devicehub.net )
    
char clientId[]  = "ArduinoEthernetClient";
 
//complete this fields with your personal acount data  
#define API_KEY        "your api key"
#define PROJECT_ID     "your project id"
#define ACTUATOR_NAME  "name of actuator"
#define DEVICE_UUID    "your device id"
             
boolean conn = false;

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

EthernetClient eth;
PubSubClient pubClient("mqtt.devicehub.net", 1883, callback, eth);
DeviceHub  client(PROJECT_ID, DEVICE_UUID, API_KEY, pubClient);

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  client.callback(topic, payload, length);
}


void setup()  
{
  Serial.begin(9600);
  Ethernet.begin(mac);
  if(client.connect(clientId)){
    conn = true;
  }
}

void loop()  
{
  
  if(conn)  
  {
      delay(3000);
      client.addActuator(ACTUATOR_NAME);
  }
  client.loop();
}
