#include "DeviceHub.h"


DeviceHub::DeviceHub(project_id_t project_id, device_uuid_t device_id, api_key_t api_key, PubSubClient& pahoClient){
    
    strncpy(this->api_key, api_key, sizeof(uuid_string_t));
    strncpy(this->project_id, project_id, sizeof(uuid_sstring_t));
    strncpy(this->device_id, device_id, sizeof(uuid_string_t));

    this->pahoClient = &pahoClient;
    
}


bool DeviceHub::connect(char clientId[]) {

    return pahoClient->connect(clientId);

}


void DeviceHub::callback(char topic[], byte payload[], unsigned int length){
   
    int i = 0;
    char message_buffer[150];

    // create buffer with null terminator
    for(i=0; i<length; i++) {
        message_buffer[i] = payload[i];
    }
    message_buffer[i] = '\0';
  
    String msgString = String(message_buffer).substring(43,44);
  
    Serial.println("message arrived: " + msgString);
  
    if(msgString == "0"){ 
    }
    else {
    }

} 


void DeviceHub::autoconfigure() {
}

 
void DeviceHub::sendSensor(char sensorName[], long int value) {

    char topic[TOPIC_SIZE];
    char payload[PAYLOAD_SIZE];
   
    sprintf(topic, "/a/%s/p/%s/d/%s/sensor/%s/data", api_key, project_id, device_id, sensorName);
    sprintf(payload, "{\"value\":%ld}", value);
    pahoClient->publish(topic, payload);

}



 
void DeviceHub::addActuator(char actuatorName[]) {
    
    char topic[TOPIC_SIZE];
    sprintf(topic, "/a/%s/p/%s/d/%s/actuator/%s/state", api_key, project_id, device_id, actuatorName);
    pahoClient->subscribe(topic);

}


void DeviceHub::loop(){

    pahoClient->loop();

}


void DeviceHub::disconnect() {

    pahoClient->disconnect();

}