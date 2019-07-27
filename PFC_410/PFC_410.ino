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

  eepromRead();
 
  SerialBT.begin("PFC410"); //Bluetooth device name

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
      Serial.println("The device started, now you can pair it with bluetooth!");  
      Serial.print("\nConexion not achieved, insert SSID and Pass");
      useBT=connectUsingBT();
      if(useBT){
        con = true;
        Serial.println("Using Bluetooth connection");
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
// listen for incoming clients
WiFiClient client = server.available();
if (client) {
  Serial.println("New client");
  memset(linebuf,0,sizeof(linebuf));
  int charcount=0;
  // an http request ends with a blank line
  boolean currentLineIsBlank = true;
  while (client.connected()) 
  {
    if (client.available()) 
        {
            char c = client.read();
            //Serial.write(c);
            //read char by char HTTP request
            linebuf[charcount]=c;
            if (charcount < sizeof(linebuf)-1) 
                charcount++;
 
            if (c == '\n' && currentLineIsBlank)
            {
                sendPage(&client);
                break;
            }
 
            if(c=='\n'){
                currentLineIsBlank = true;
                Serial.printf("Comeca aqui", linebuf);
                if(hasGet(linebuf)){
                    parseRequest(linebuf, &client);                
                }
                memset(linebuf,0,sizeof(linebuf));
            }
            else if (c != '\r')
            {
                // you've gotten a character on the current line
                currentLineIsBlank = false;
            }
        }
 
   scrollDisplay();
  }
  // give the web browser time to receive the data
  delay(1);

  client.stop();
  Serial.println("client disconnected");
    
  }
}
