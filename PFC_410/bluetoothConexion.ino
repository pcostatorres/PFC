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
        //Serial.println("Valor inserido");
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
        //Serial.println("Valor inserido");
        return true;
      }  
    }
  }  
  return false;
 
}

void processBT(){
  
  char buf[32];
  
  if(SerialBT.available()){
    
    memset(buf,0,sizeof(buf));
    Serial.println("Conectado3");
    String nom = SerialBT.readStringUntil('\n');
    int len = nom.length();
    nom.toCharArray(buf , len);
    
  
    clearDisplay();    
    char *param1 = strstr(buf, "Linha1=") + 7;
    char *param2 = strstr(buf, "Linha2=") + 7;
  
    char *end = strstr(param1, "&");
    *end = '\0';  // Terminador
    end = strstr(param2, "&");
    *end = '\0';
  
    Serial.printf("Parametro 1: %s\n", param1);
    Serial.printf("Parametro 2: %s\n", param2);
    drawtext(0,0,param1,7);
    drawtext(0,8,param2,2);    

  }
  scrollDisplay();
  
}
