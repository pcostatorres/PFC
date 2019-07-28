//Dimensao matriz RGB
#define NLIN 16
#define NCOL 32
#define TEXT_LINES 2
#define CHAR_LINE 7
#define FONT_WIDTH 5
#define FONT_HEIGHT 8
#define NCOL_MEM (FONT_WIDTH+1)*CHAR_LINE
#define NLIN_MEM TEXT_LINES*FONT_HEIGHT

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

extern int displayRGB [NLIN_MEM][NCOL_MEM];
extern int scroll_horizontal;
extern int scroll_vertical;

void ledMatrixInit();
void clearDisplay();
void displayMem();
void changeColor(int);
void activeLine(int );
int drawchar(int, int,int, int);
void drawtext(int , int , char* ,int );
void displayDriver(void*);
void serialWritting(int *,int *);
void scrollDisplay();
