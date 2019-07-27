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

//Dimensao matriz RGB
#define NLIN 16
#define NCOL 32
#define TEXT_LINES 2
#define CHAR_LINE 7
#define FONT_WIDTH 5
#define FONT_HEIGHT 8
#define NCOL_MEM (FONT_WIDTH+1)*CHAR_LINE
#define NLIN_MEM TEXT_LINES*FONT_HEIGHT

//Dimensao matriz Output
#define SIZEARRAY 64
#define SELECT 8

int delayTime =0;
