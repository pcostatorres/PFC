#include <WiFi.h>
#include "ledMatrixDriver.h"
#include "wifiConnection.h"
#include "BluetoothSerial.h"
#include "bluetoothConnection.h"
#include "EEPROM.h"

#define RETRIES 20
bool useBT=false;
WiFiServer server(80);

bool connectionInit(){
  int retries = RETRIES; 
  bool con = false;
  bool useBT = false;

  connectionDisplayStatus(0,0,1);
  connectionDisplayStatus(0,1,1);
  
  while(!con){    
    // We start by connecting to a WiFi network 
    wifiBegin();

    // attempt to connect to Wifi network:
    while(WiFi.status() != WL_CONNECTED && retries>0){
      // Connect to WPA/WPA2 network.
      delay(500);
      Serial.print(".");
      retries--;
    }  
    
    if(retries==0){

      SerialBT.begin("PFC410"); //Bluetooth device name
      Serial.println("\nThe device started, now you can pair it with bluetooth!");  
      Serial.println("Conexion not achieved, insert SSID and Pass\n");
      //WAIT STATUS
      connectionDisplayStatus(0,1,5);
  
      useBT = connectUsingBT();
      
      //CONNECTING STATUS
      connectionDisplayStatus(0,1,1);
      if(useBT){
        con = true;
        Serial.println("\nUsing Bluetooth connection");
        connectionDisplayStatus(0,1,4);  
      }
      retries = RETRIES;
    }else 
      con = true;
  }

  if(!useBT){
    wifiConnectionInfo(&server);
    eepromWrite();
  }
  return useBT;
}

                                                   
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

  useBT = connectionInit();
  
}


void loop() {
  
bool connectionStatus = false;

  if(!useBT){
    connectionStatus = wifiProcess();  
  }else {
    connectionStatus = processBT();
  }
  if(connectionStatus == false){
    useBT = connectionInit();
  }
  
}
