//Tirar o .h e incluir .cpp

#include "interface.h"
#include "refreshDisplay.h"
#include "driver.h"
#include "wifiCode.h"
#include "BluetoothSerial.h"
#include "bluetoothConexion.h"
#include "EEPROM.h"
#include "eepromReadWrite.h"
//#include "html.h"

//auto include .c arduino

#define RETRIES 30

unsigned long timeStamp = 0;
int retries = RETRIES;
                                                   
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  eepromRead();
  
  SerialBT.begin("PFC410"); //Bluetooth device name
  //Serial.println("The device started, now you can pair it with bluetooth!");  

  pinMode(SCLK_PIN,OUTPUT);
  pinMode(R1,OUTPUT);
  pinMode(G1,OUTPUT);
  pinMode(B1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(G2,OUTPUT);
  pinMode(B2,OUTPUT);
  
  pinMode(OE,OUTPUT);
  pinMode(LAT,OUTPUT);
  
  pinMode(SELA, OUTPUT);
  pinMode(SELB, OUTPUT);
  pinMode(SELC, OUTPUT);
  pinMode(SELD, OUTPUT);
  digitalWrite(OE,0);
  digitalWrite(LAT,1);
  
  clearDisplay();
  while(!Serial) {
  }
   
  // We start by connecting to a WiFi network 
  wifiBegin();
  
  // attempt to connect to Wifi network:
  while(WiFi.status() != WL_CONNECTED & retries>0){
    // Connect to WPA/WPA2 network.
    delay(500);
    Serial.print(".");
    retries--;
  }

  if(retries==0){
      //SerialBT.begin("PFC410"); //Bluetooth device name
      Serial.println("The device started, now you can pair it with bluetooth!");  
      Serial.print("\nConexion not achieved, insert SSID and Pass");
      connectUsingBT();
      retries = RETRIES;
    }
  

  wifiConexion();

  eepromWrite();
}

void loop() {
// listen for incoming clients
WiFiClient client = server.available();
if (client) {
  Serial.println("New client");
  memset(linebuf,0,sizeof(linebuf));
  charcount=0;
  int linecount=0;
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
                //Serial.printf("Comeca aqui", linebuf);
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
 
    if(timeStamp<millis()){ 
      //changeColor(c++);
      timeStamp = millis()+500;
      scroll_horizontal=scroll_horizontal==0?NCOL_MEM-NCOL:scroll_horizontal-1;
      scroll_horizontal=scroll_horizontal<0?NCOL_MEM-NCOL:scroll_horizontal;

      scroll_vertical=scroll_vertical==0?NLIN_MEM-NLIN:scroll_vertical-1;
      scroll_vertical=scroll_vertical<0?NLIN_MEM-NLIN:scroll_vertical;
      displayMem();
      
    }
    displayDriver();
  }
  // give the web browser time to receive the data
  delay(1);

  client.stop();
  Serial.println("client disconnected");
    
  }
}
