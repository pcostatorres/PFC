#include <WiFi.h>
#include "ledMatrixDriver.h"
#include "wifiCode.h"
#include "BluetoothSerial.h"
#include "bluetoothConexion.h"
#include "EEPROM.h"

#define RETRIES 20

WiFiServer server(80);

char linebuf[80];
int retries = RETRIES;
bool useBT=false;
bool con = false;
                                                   
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //eepromRead();
 
  //SerialBT.begin("PFC410"); //Bluetooth device name

  ledMatrixInit();
 
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
      Serial.print("\nConexion not achieved, insert SSID and Pass\n");
      
      useBT = connectUsingBT();
      
      if(useBT){
        con = true;
        Serial.println("\nUsing Bluetooth connection");
      }
      retries = RETRIES;
    }else 
      con = true;
  }
  
  if(!useBT){
    wifiConexionInfo(&server);
    eepromWrite();
  }
}

void loop() {

  if(!useBT){
    wifiProcess();
  }else {
    processBT();
  }
  
}
