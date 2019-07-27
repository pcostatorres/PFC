#include "wifiCode.h"

#define EEPROM_SIZE 66
#define EEPROM_SSID 0
#define EEPROM_PASS 32

char EEPROMBuf[EEPROM_SIZE];

void eepromRead(){
//Leitura EEPROM
  if (!EEPROM.begin(EEPROM_SIZE)){
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
  for (int i = 0; i < EEPROM_SIZE; i++){
    EEPROMBuf[i]=byte(EEPROM.read(i));
  }

  memcpy(ssid, &EEPROMBuf[0], EEPROMBuf[EEPROM_SIZE-2]); 
  memcpy(password, &EEPROMBuf[32],EEPROMBuf[EEPROM_SIZE-1]);

}

void eepromWrite(){
  //escrita na EEPROM
  memset(EEPROMBuf, 0 , 32);
  memcpy(&EEPROMBuf[0], ssid, strlen(ssid));
  memset(EEPROMBuf + 32, 0 , 32); 
  memcpy(&EEPROMBuf[32], password, strlen(password));
  EEPROMBuf[EEPROM_SIZE-2] = strlen(ssid);
  EEPROMBuf[EEPROM_SIZE-1] = strlen(password);

  for(int i=0;i<EEPROM_SIZE;i++){
    EEPROM.write(i, EEPROMBuf[i]);  
    EEPROM.commit(); 
    EEPROMBuf[i];
    //Serial.print(EEPROMBuf[i]);
  } 
}
