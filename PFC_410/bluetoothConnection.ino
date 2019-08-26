#include "bluetoothConnection.h"
#include "wifiConnection.h"
#include "commands.h"
//#include "textInterface.h"

#define DEFAULTCOLOR 1

#define BUFFERSTRING 100

bool hasText = false;

enum { BLUE_REQ = 0, SSID_REQ, PASS_REQ, END_REQ };

BluetoothSerial SerialBT;

int connectUsingBT(){

  char buf[32];

  SerialBT.begin("PFC410"); //Bluetooth device name
  Serial.println("\nThe device started, now you can pair it with bluetooth!");  
  Serial.println("Conexion not achieved, insert SSID and Pass\n");
  //WAIT STATUS
  connectionDisplayStatus(0,1,5);  
  
  while(!SerialBT.hasClient());
    
  SerialBT.print("Credentials");
  
  int state=BLUE_REQ;
  
  while(state != END_REQ){
  
    while(SerialBT.available()){

      String nom = SerialBT.readStringUntil('\n');
      int len = nom.length();
      nom.toCharArray(buf , len);

      switch (state){

        case BLUE_REQ:
          if(memcmp("BLUE", buf, 4)==0){    
            Serial.println("\nUsing Bluetooth connection");
            connectionDisplayStatus(0,1,4);      
            return BT;
          }
          else if(memcmp("SSID", buf, 4)==0){      
            memcpy(ssid,buf+4,len-4);
            Serial.println("Insert PASS:");
            state=PASS_REQ;
          }
          break;
          
        case PASS_REQ:          
          if(memcmp("PASS", buf, 4)==0){
            memcpy(password,buf+4,len-4);
            return WIFI;
          }
          break;
        default: 
          break;

      }
    }  
  }    
  return NCON; 
}


int processBT(){
  
  char buf[BUFFERSTRING];

  if(SerialBT.available()){
    
    memset(buf,0,sizeof(buf));
    
    String nom = SerialBT.readStringUntil('\n');
    int len = nom.length();
    nom.toCharArray(buf , len);

    if(strcmp(buf,"WIFISTART")==0){
      clearDisplay();
      //SerialBT.flush();
      //SerialBT.end();
      return NCON;
    }
  
    clearDisplay();   
    parseCommands(buf, len);  
     
    hasText = true;
    //Linha1=TESTE&Linha2=teste&Cor1=1&Cor2=6
  }
  if(hasText) scrollDisplay();
  
  return BT;
  
}
