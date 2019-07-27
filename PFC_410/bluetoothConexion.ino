#include "wifiCode.h"

BluetoothSerial SerialBT;

bool connectUsingBT(){

//utilizar security code
//ssid + pass usar carater final com
  char buf[32];

  while(!SerialBT.hasClient());
  
  SerialBT.print("Credentials");

  int flag=0;

  while(flag!=3){

    if(SerialBT.available()){
      String nom = SerialBT.readStringUntil('\n');
      int len = nom.length();
      nom.toCharArray(buf , len);
      
      if(memcmp("SSID", buf, 4)==0){
       
        memcpy(ssid,buf+4,len-4);
        flag+=1;
        Serial.println("Valor inserido");
      }
      else if(memcmp("PASS", buf, 4)==0){
        memcpy(password,buf+4,len-4);
        flag+=1;
      }
      else if(memcmp("WIFI", buf, 4)==0){
        flag+=1;
        return false;      
      }
      else if(memcmp("BLUE", buf, 4)==0){
        return true;
      }  
    }
  }  
  return false;
 
}
