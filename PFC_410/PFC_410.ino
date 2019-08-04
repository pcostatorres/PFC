#include <WiFi.h>
#include "ledMatrixDriver.h"
#include "wifiConnection.h"
#include "bluetoothConnection.h"
#include "EEPROM.h"

#define RETRIES 20
enum processSelection{ WIFI = 0, BT, NCON};
WiFiServer server(80);
int connectionStatus = NCON;

void connectionInit(){

  connectionDisplayStatus(0,0,1);
  connectionDisplayStatus(0,1,1);
  connectionStatus = WIFI;
  
  while(connectionStatus == WIFI){    
    // We start by connecting to a WiFi network 
       
    if(wifiBegin(RETRIES) == 0){
      connectionStatus = connectUsingBT();
      
    } else{
      wifiConnectionInfo(&server);
      eepromWrite();
      break;
    }
  }
}
      //CONNECTING STATUS
      //connectionDisplayStatus(0,1,1);
                                                   
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //eepromRead();

  ledMatrixInit();
  clearDisplay();

  xTaskCreate(
      displayDriver,          /* Task function. */
      "displayDriver",        /* String with name of task. */
      10000,            /* Stack size in bytes. */
      NULL,             /* Parameter passed as input of the task */
      2,                /* Priority of the task. */
      NULL);            /* Task handle. */
  
}

void loop() {

  switch(connectionStatus){

    case WIFI:
      connectionStatus = wifiProcess();
      break;
    case BT:
      connectionStatus = processBT(); 
      //colocar acesso wifi
      break;
    default:
      connectionInit();
      break;
  }
}  
  
