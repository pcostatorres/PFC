#include "wifiConnection.h"
bool hasText = false;

enum { BLUE_REQ = 0, SSID_REQ, PASS_REQ, END_REQ };

BluetoothSerial SerialBT;

bool connectUsingBT(){

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
  
  return BT;
  
}
