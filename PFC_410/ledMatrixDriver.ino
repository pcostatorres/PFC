#include "font.h"
#include "ledMatrixDriver.h"
#include "textInterface.h"

int delayTime = 0;
int arrayTx[SELECT][SIZEARRAY];

void ledMatrixInit(){

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
}

void clearDisplay(){
//faz a limpeza de todos os bits presentes nos shift register  
  for(int i=0;i<SIZEARRAY;i++){
     
     digitalWrite(OE,0);
     digitalWrite(LAT,1);
     
     digitalWrite(SCLK_PIN,1);
     digitalWrite(SCLK_PIN,0);     
  }
  memset(displayRGB,0,sizeof(displayRGB));
}

void activeLine(int line){

  digitalWrite(SELA,1);
  digitalWrite(SELB,1);
  digitalWrite(SELC,1);
  digitalWrite(SELD,1);
  if (line == 0){
    digitalWrite(SELA,0);
  }
  if (line == 1){
    digitalWrite(SELB,0);
  }
   if (line == 2){
    digitalWrite(SELC,0);
  } 
  if (line == 3){
    digitalWrite(SELD,0);
  }
}


void displayDriver(void * param){
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 2;

  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  while(true){
    for(int i=0;i<4;i++){
      
      digitalWrite(OE,1);
      digitalWrite(LAT,0);
      serialWritting(arrayTx[i],arrayTx[i+4]);
      digitalWrite(LAT,1);
      activeLine(i);
      digitalWrite(OE,0);   
      //delay(1/10);      
      // Wait for the next cycle.
      vTaskDelayUntil( &xLastWakeTime, xFrequency );
       
    } 
  }
  vTaskDelete( NULL );
}

void serialWritting(int *high,int *low){
  for(int i=SIZEARRAY-1; i>=0 ;i--){

     digitalWrite(R1,(high[i]&1)!=0?1:0);
     digitalWrite(R2,(low[i]&1)!=0?1:0);    

     digitalWrite(G1,(high[i]&2)!=0?1:0);
     digitalWrite(G2,(low[i]&2)!=0?1:0);    
     
     digitalWrite(B1,(high[i]&4)!=0?1:0);
     digitalWrite(B2,(low[i]&4)!=0?1:0);    
     
     digitalWrite(SCLK_PIN,1);
     digitalWrite(SCLK_PIN,0); 
     delay(delayTime);
  }  
}
