//Dimensao matriz RGB
#define NLIN 16
#define NCOL 32
#define TEXT_LINES 2
#define CHAR_LINE 7
#define FONT_WIDTH 5
#define FONT_HEIGHT 8
#define NCOL_MEM (FONT_WIDTH+1)*CHAR_LINE
#define NLIN_MEM TEXT_LINES*FONT_HEIGHT

void clearDisplay();
void changeColor(int);
int drawchar(int, int,int, int);
void drawtext(int , int , char* ,int );
void scrollDisplay();
void connectionDisplayStatus(int , int , int );
