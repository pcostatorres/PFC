#define SCLK_PIN 4
#define OE 15
#define LAT 33
#define R1 21
#define G1 17
#define B1 16
#define R2 19
#define G2 18
#define B2 5
#define SELA 23
#define SELB 22
#define SELC 14
#define SELD 32
#define ROW 16
#define COLUMN 32

int displayRGB [32][16];    

//Vectores 64 bits
int SR1 [64] = {1,0,0,1,0,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,0}; 
int SG1 [64] = {1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0};                  
int SB1 [64] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};       

int SR2 [64] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};      
int SG2 [64] = {1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0};  
int SB2 [64] = {0,0,0,0,0,1,0,0, 0,0,1,0,0,0,0,0, 0,0,0,1,0,0,0,0, 0,1,0,0,0,1,0,0, 0,1,0,0,0,1,0,0, 0,1,0,0,0,1,0,0, 0,1,0,0,0,1,0,0, 0,1,0,0,0,1,0,0};                                                        
//Selectores de linhas (ABCD)
int SEL[4];


                
void clearDisplay(){
  for(int i=0;i<64;i++){
    
     //digitalWrite(G1,0);
     //digitalWrite(B1,0);
     
     digitalWrite(OE,0);
     digitalWrite(LAT,1);
     
     digitalWrite(SCLK_PIN,1);
     digitalWrite(SCLK_PIN,0);
     //digitalWrite(LAT,0);
  }
}

/*
void displayMem(){

  //Linhas
  for(int i=0;i<ROW;i++){
    //Colunas
    for(int j=0;j<COLUMN;j++){

      if(i<4 && j<8){
        
        SEL[i][56+j] = displayRGB [i][j];
      }
      else if(i>3 && j<8){

       SEL[i-4][55-j] = displayRGB [i][j];
      }
      


      
    }
  }
  
}*/

void displayDriver(){

  
  
  
}


void serialWritting(int SR1 [],int SG1 [], int SB1 [], int SR2 [],int SG2 [],int SB2[], int SEL[]){

    digitalWrite(SELA,SEL[0]);
    digitalWrite(SELB,SEL[1]);
    digitalWrite(SELC,SEL[2]);
    digitalWrite(SELD,SEL[3]);
  
  for(int i=0; i<64 ;i++){
    
     digitalWrite(R1,SR1[i]);
     digitalWrite(G1,SG1[i]);
     digitalWrite(B1,SB1[i]);
     digitalWrite(R2,SR2[i]);
     digitalWrite(G2,SG2[i]);
     digitalWrite(B2,SB2[i]);
  
     digitalWrite(SCLK_PIN,1);
     digitalWrite(SCLK_PIN,0); 
     delay(500);
  }
  
  //digitalWrite(LAT,1);
  
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
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
  
  clearDisplay();
  delay(5000);
  
  
  //serialWritting(SR1,SG1,SB1,SR2,SG2,SB2,SEL);
}

void loop() {

  scanf("%d %d %d %d", SEL[0],SEL[1],SEL[2],SEL[3]);          
  serialWritting(SR1,SG1,SB1,SR2,SG2,SB2,SEL);
}
