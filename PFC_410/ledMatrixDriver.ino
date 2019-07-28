#include "font.h"
#include "ledMatrixDriver.h"

int scroll_horizontal = 0;
int scroll_vertical = 0;
int c = 1;
int delayTime = 0;
unsigned long timeStamp = 0;

int displayRGB [NLIN_MEM][NCOL_MEM];
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

const int convTable[NLIN][NCOL] = {
{0<<8|56,0<<8|57,0<<8|58,0<<8|59,0<<8|60,0<<8|61,0<<8|62,0<<8|63,0<<8|40,0<<8|41,0<<8|42,0<<8|43,0<<8|44,0<<8|45,0<<8|46,0<<8|47,0<<8|24,0<<8|25,0<<8|26,0<<8|27,0<<8|28,0<<8|29,0<<8|30,0<<8|31,0<<8|8,0<<8|9,0<<8|10,0<<8|11,0<<8|12,0<<8|13,0<<8|14,0<<8|15},
{1<<8|56,1<<8|57,1<<8|58,1<<8|59,1<<8|60,1<<8|61,1<<8|62,1<<8|63,1<<8|40,1<<8|41,1<<8|42,1<<8|43,1<<8|44,1<<8|45,1<<8|46,1<<8|47,1<<8|24,1<<8|25,1<<8|26,1<<8|27,1<<8|28,1<<8|29,1<<8|30,1<<8|31,1<<8|8,1<<8|9,1<<8|10,1<<8|11,1<<8|12,1<<8|13,1<<8|14,1<<8|15},
{2<<8|56,2<<8|57,2<<8|58,2<<8|59,2<<8|60,2<<8|61,2<<8|62,2<<8|63,2<<8|40,2<<8|41,2<<8|42,2<<8|43,2<<8|44,2<<8|45,2<<8|46,2<<8|47,2<<8|24,2<<8|25,2<<8|26,2<<8|27,2<<8|28,2<<8|29,2<<8|30,2<<8|31,2<<8|8,2<<8|9,2<<8|10,2<<8|11,2<<8|12,2<<8|13,2<<8|14,2<<8|15},
{3<<8|56,3<<8|57,3<<8|58,3<<8|59,3<<8|60,3<<8|61,3<<8|62,3<<8|63,3<<8|40,3<<8|41,3<<8|42,3<<8|43,3<<8|44,3<<8|45,3<<8|46,3<<8|47,3<<8|24,3<<8|25,3<<8|26,3<<8|27,3<<8|28,3<<8|29,3<<8|30,3<<8|31,3<<8|8,3<<8|9,3<<8|10,3<<8|11,3<<8|12,3<<8|13,3<<8|14,3<<8|15},
{0<<8|55,0<<8|54,0<<8|53,0<<8|52,0<<8|51,0<<8|50,0<<8|49,0<<8|48,0<<8|39,0<<8|38,0<<8|37,0<<8|36,0<<8|35,0<<8|34,0<<8|33,0<<8|32,0<<8|23,0<<8|22,0<<8|21,0<<8|20,0<<8|19,0<<8|18,0<<8|17,0<<8|16,0<<8|7,0<<8|6,0<<8|5,0<<8|4,0<<8|3,0<<8|2,0<<8|1,0<<8|0},
{1<<8|55,1<<8|54,1<<8|53,1<<8|52,1<<8|51,1<<8|50,1<<8|49,1<<8|48,1<<8|39,1<<8|38,1<<8|37,1<<8|36,1<<8|35,1<<8|34,1<<8|33,1<<8|32,1<<8|23,1<<8|22,1<<8|21,1<<8|20,1<<8|19,1<<8|18,1<<8|17,1<<8|16,1<<8|7,1<<8|6,1<<8|5,1<<8|4,1<<8|3,1<<8|2,1<<8|1,1<<8|0},
{2<<8|55,2<<8|54,2<<8|53,2<<8|52,2<<8|51,2<<8|50,2<<8|49,2<<8|48,2<<8|39,2<<8|38,2<<8|37,2<<8|36,2<<8|35,2<<8|34,2<<8|33,2<<8|32,2<<8|23,2<<8|22,2<<8|21,2<<8|20,2<<8|19,2<<8|18,2<<8|17,2<<8|16,2<<8|7,2<<8|6,2<<8|5,2<<8|4,2<<8|3,2<<8|2,2<<8|1,2<<8|0},
{3<<8|55,3<<8|54,3<<8|53,3<<8|52,3<<8|51,3<<8|50,3<<8|49,3<<8|48,3<<8|39,3<<8|38,3<<8|37,3<<8|36,3<<8|35,3<<8|34,3<<8|33,3<<8|32,3<<8|23,3<<8|22,3<<8|21,3<<8|20,3<<8|19,3<<8|18,3<<8|17,3<<8|16,3<<8|7,3<<8|6,3<<8|5,3<<8|4,3<<8|3,3<<8|2,3<<8|1,3<<8|0},
{4<<8|56,4<<8|57,4<<8|58,4<<8|59,4<<8|60,4<<8|61,4<<8|62,4<<8|63,4<<8|40,4<<8|41,4<<8|42,4<<8|43,4<<8|44,4<<8|45,4<<8|46,4<<8|47,4<<8|24,4<<8|25,4<<8|26,4<<8|27,4<<8|28,4<<8|29,4<<8|30,4<<8|31,4<<8|8,4<<8|9,4<<8|10,4<<8|11,4<<8|12,4<<8|13,4<<8|14,4<<8|15},
{5<<8|56,5<<8|57,5<<8|58,5<<8|59,5<<8|60,5<<8|61,5<<8|62,5<<8|63,5<<8|40,5<<8|41,5<<8|42,5<<8|43,5<<8|44,5<<8|45,5<<8|46,5<<8|47,5<<8|24,5<<8|25,5<<8|26,5<<8|27,5<<8|28,5<<8|29,5<<8|30,5<<8|31,5<<8|8,5<<8|9,5<<8|10,5<<8|11,5<<8|12,5<<8|13,5<<8|14,5<<8|15},
{6<<8|56,6<<8|57,6<<8|58,6<<8|59,6<<8|60,6<<8|61,6<<8|62,6<<8|63,6<<8|40,6<<8|41,6<<8|42,6<<8|43,6<<8|44,6<<8|45,6<<8|46,6<<8|47,6<<8|24,6<<8|25,6<<8|26,6<<8|27,6<<8|28,6<<8|29,6<<8|30,6<<8|31,6<<8|8,6<<8|9,6<<8|10,6<<8|11,6<<8|12,6<<8|13,6<<8|14,6<<8|15},
{7<<8|56,7<<8|57,7<<8|58,7<<8|59,7<<8|60,7<<8|61,7<<8|62,7<<8|63,7<<8|40,7<<8|41,7<<8|42,7<<8|43,7<<8|44,7<<8|45,7<<8|46,7<<8|47,7<<8|24,7<<8|25,7<<8|26,7<<8|27,7<<8|28,7<<8|29,7<<8|30,7<<8|31,7<<8|8,7<<8|9,7<<8|10,7<<8|11,7<<8|12,7<<8|13,7<<8|14,7<<8|15},
{4<<8|55,4<<8|54,4<<8|53,4<<8|52,4<<8|51,4<<8|50,4<<8|49,4<<8|48,4<<8|39,4<<8|38,4<<8|37,4<<8|36,4<<8|35,4<<8|34,4<<8|33,4<<8|32,4<<8|23,4<<8|22,4<<8|21,4<<8|20,4<<8|19,4<<8|18,4<<8|17,4<<8|16,4<<8|7,4<<8|6,4<<8|5,4<<8|4,4<<8|3,4<<8|2,4<<8|1,4<<8|0},  
{5<<8|55,5<<8|54,5<<8|53,5<<8|52,5<<8|51,5<<8|50,5<<8|49,5<<8|48,5<<8|39,5<<8|38,5<<8|37,5<<8|36,5<<8|35,5<<8|34,5<<8|33,5<<8|32,5<<8|23,5<<8|22,5<<8|21,5<<8|20,5<<8|19,5<<8|18,5<<8|17,5<<8|16,5<<8|7,5<<8|6,5<<8|5,5<<8|4,5<<8|3,5<<8|2,5<<8|1,5<<8|0},
{6<<8|55,6<<8|54,6<<8|53,6<<8|52,6<<8|51,6<<8|50,6<<8|49,6<<8|48,6<<8|39,6<<8|38,6<<8|37,6<<8|36,6<<8|35,6<<8|34,6<<8|33,6<<8|32,6<<8|23,6<<8|22,6<<8|21,6<<8|20,6<<8|19,6<<8|18,6<<8|17,6<<8|16,6<<8|7,6<<8|6,6<<8|5,6<<8|4,6<<8|3,6<<8|2,6<<8|1,6<<8|0},
{7<<8|55,7<<8|54,7<<8|53,7<<8|52,7<<8|51,7<<8|50,7<<8|49,7<<8|48,7<<8|39,7<<8|38,7<<8|37,7<<8|36,7<<8|35,7<<8|34,7<<8|33,7<<8|32,7<<8|23,7<<8|22,7<<8|21,7<<8|20,7<<8|19,7<<8|18,7<<8|17,7<<8|16,7<<8|7,7<<8|6,7<<8|5,7<<8|4,7<<8|3,7<<8|2,7<<8|1,7<<8|0}};


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


void displayMem(){
//Passa valor da matriz painel para a matriz de coversao
  //Linhas
  for(int i=0 ;i<NLIN;i++){    
    //Colunas
    for(int j=0;j<NCOL;j++){
        arrayTx[convTable[i][j]>>8][convTable[i][j]&0xff] = displayRGB[i+scroll_vertical][j+scroll_horizontal];
   
    }
  }    
}

void changeColor(int color){

  for(int i=0;i<NLIN;i++){
    for(int j=0;j<NCOL;j++){

      displayRGB[i][j] = displayRGB[i][j] == 0?0:color;
    }
  }
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

int drawchar(int x, int y, int c, int color){
//recebe pos x,y e o caracter
  int w,h, *d_char;
  d_char = font + ( 8 * (c-32));
  for (h=0; h < 8; h++){  
    for(w=0; w < 5; w++){
      if(*d_char & (0x80 >> w)){
        displayRGB[h+y][w+x] = color;
      }else 
        displayRGB[h+y][w+x] = 0;       
    }
    d_char += 1;
  }
  return x+6;
}

void drawtext(int x, int y, char *text,int color){
  while(*text){
    x=drawchar(x,y,*text++,color);
  }
  displayMem();
}

void displayDriver(void* param){
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 1;

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
      delay(1/10);      
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

void scrollDisplay(){
  if(timeStamp<millis()){ 
      //changeColor(c++);
      timeStamp = millis()+500;
      scroll_horizontal=scroll_horizontal==0?NCOL_MEM-NCOL:scroll_horizontal-1;
      scroll_horizontal=scroll_horizontal<0?NCOL_MEM-NCOL:scroll_horizontal;

      scroll_vertical=scroll_vertical==0?NLIN_MEM-NLIN:scroll_vertical-1;
      scroll_vertical=scroll_vertical<0?NLIN_MEM-NLIN:scroll_vertical;
      displayMem();
      
    }
    //displayDriver();
}    
