#include "textInterface.h"

//Output pin ESP32
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

//Dimensao matriz Output
#define SIZEARRAY 64
#define SELECT 8

#define LINE_SEL 4

void updateDisplayMem(int [NLIN_MEM][NCOL_MEM], int , int );
void updateDisplayMem();
void ledMatrixInit();
void clearDisplayMatrix();
void activeLine(int );
void displayDriver(void*);
void serialWritting(int *,int *);
