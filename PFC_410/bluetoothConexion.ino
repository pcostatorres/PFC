#include "wifiCode.h"
bool hasText = false;

BluetoothSerial SerialBT;

bool connectUsingBT(){

  char buf[32];
  
  while(!SerialBT.hasClient());
    
  SerialBT.print("Credentials");
  
  int flag=0;
  
  while(flag!=3){
  
    while(SerialBT.available()){

      String nom = SerialBT.readStringUntil('\n');
      int len = nom.length();
      nom.toCharArray(buf , len);
      
      if(memcmp("SSID", buf, 4)==0){
       
        memcpy(ssid,buf+4,len-4);
        flag+=1;
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

char *chrinstr(const char *str, char c, char len) {
  if (str == NULL) return 0;
  while (*str) {
    if (*str == c)
      break;
    str += 1;
    if((--len) == 0)
      return NULL;
  }
  return (char*)str;
}

bool processBT(){
  
  char buf[100];

  if(SerialBT.available()){
    
    memset(buf,0,sizeof(buf));
    
    String nom = SerialBT.readStringUntil('\n');
    int len = nom.length();
    nom.toCharArray(buf , len);
  
    clearDisplay();    
    char *param1 = strstr(buf, "Linha1=") + 7;
    char *param2 = strstr(buf, "Linha2=") + 7;
    char *param3 = strstr(buf, "Cor1=") + 5;
    char *param4 = strstr(buf, "Cor2=") + 5;
    
    char *end = strstr(param1, "$");
    *end = '\0';  // Terminador
    end = strstr(param2, "$");
    *end = '\0';
    end = strstr(param3, "#");
    *end = '\0';
    end = strstr(param4, "#");
    *end = '\0';  
    
    int cor1 = atoi(param3);
    int cor2 = atoi(param4);
    
    drawtext(0,0,param1,cor1);
    drawtext(0,8,param2,cor2);  
    hasText = true;
    //Linha1=TESTE$Linha2=teste$Cor1=1#Cor2=6#
  }
  if(hasText) scrollDisplay();
  
  return true;
  
}
