#include "wifiConnection.h"

#define EEPROM_SIZE 128
#define EEPROM_SSID_OFFSET (EEPROM_SSID_LEN+1)
#define EEPROM_PASS_OFFSET (EEPROM_PASS_LEN+1)
#define EEPROM_SSID_LEN 0
#define EEPROM_PASS_LEN (EEPROM_SIZE/2)

char EEPROMBuf[EEPROM_SIZE];

void eepromRead(){
//Leitura EEPROM
  if (!EEPROM.begin(EEPROM_SIZE)){
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
  for (int i = 0; i < EEPROM_SIZE; i++){
    EEPROMBuf[i]=byte(EEPROM.read(i));
  }
  memcpy(ssid, &EEPROMBuf[EEPROM_SSID_OFFSET], EEPROMBuf[EEPROM_SSID_LEN]); 
  memcpy(password, &EEPROMBuf[EEPROM_PASS_OFFSET],EEPROMBuf[EEPROM_PASS_LEN]);
}

void eepromWrite(){
  //escrita na EEPROM
  memset(EEPROMBuf, 0 , EEPROM_SIZE);
  memcpy(&EEPROMBuf[EEPROM_SSID_OFFSET], ssid, strlen(ssid));
  memcpy(&EEPROMBuf[EEPROM_PASS_OFFSET], password, strlen(password));
  EEPROMBuf[EEPROM_SSID_LEN] = strlen(ssid);
  EEPROMBuf[EEPROM_PASS_LEN] = strlen(password);

  for(int i=0;i<EEPROM_SIZE;i++){
    EEPROM.write(i, EEPROMBuf[i]);  
    EEPROM.commit(); 
    EEPROMBuf[i];

  } 
}
