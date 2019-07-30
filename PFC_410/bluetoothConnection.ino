#include "wifiConnection.h"
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


char *extractParameterValue(char *query, char *param, char *value, char len){
  char *ptr;
  char i;

  //Serial.println(query);
  if(query == NULL || param == NULL || value == NULL)
    return NULL;
  // Find param
  ptr = strstr(query, param);
  if(ptr == NULL || ptr >= query + len )
    return NULL;
    
  // skip param
  while(*ptr++ != '='){
    if(ptr == query + len)
      return NULL;
  }
      
  // copy value
  i = 0;
  while(*ptr != '&' && *ptr != '#' && ptr != query + len){
    *(value + i++) = *ptr++;
  }
  // end string
  *(value + i) = '\0';
  return value;
}

bool processBT(){
  
  char buf[100];
  char value[sizeof(buf)];

  if(SerialBT.available()){
    
    memset(buf,0,sizeof(buf));
    
    String nom = SerialBT.readStringUntil('\n');
    int len = nom.length();
    nom.toCharArray(buf , len);
  
    clearDisplay();   

    if(extractParameterValue(buf,"Cor1",value,sizeof(buf))==NULL){  
      Serial.println("Falha a obter parametro Cor 1");
    }
    int cor1 = atoi(value);
    
    if(extractParameterValue(buf,"Cor2",value,sizeof(buf))==NULL){  
      Serial.println("Falha a obter parametro Cor 2");
    }
    int cor2 = atoi(value);
    
    if(extractParameterValue(buf,"Linha1",value,sizeof(buf))==NULL){  
      Serial.println("Falha a obter parametro Linha 1");
    }
    drawtext(0,0,value,cor1);
    if(extractParameterValue(buf,"Linha2",value,sizeof(buf))==NULL){  
      Serial.println("Falha a obter parametro Linha 2");
    }
    drawtext(0,8,value,cor2); 
     
    hasText = true;
    //Linha1=TESTE&Linha2=teste&Cor1=1&Cor2=6
  }
  if(hasText) scrollDisplay();
  
  return true;
  
}
