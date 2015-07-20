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
#define SENSOR_NAME    "name of sensor"
#define DEVICE_UUID    "your device id"
             
boolean conn = false;

EthernetClient eth;
PubSubClient pubClient("mqtt.devicehub.net", 1883, NULL, eth);
DeviceHub  client(PROJECT_ID, DEVICE_UUID, API_KEY, pubClient);



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
      long int analog_sensor = random(0, 150.0);
      delay(3000);
      client.sendSensor(SENSOR_NAME, analog_sensor);
  }
  client.loop();
}
