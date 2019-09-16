//Dimensao matriz RGB
#define NLIN 16
#define NCOL 32
#define TEXT_LINES 2
#define CHAR_LINE 15
#define FONT_WIDTH 5
#define FONT_HEIGHT 8
#define NCOL_MEM (FONT_WIDTH+1)*CHAR_LINE
#define NLIN_MEM TEXT_LINES*FONT_HEIGHT

#define RED 1
#define PINK 5
#define BLUE 4
#define COLOR_STATE RED
#define COLOR_WAIT PINK
#define COLOR_BT BLUE

#define LED_STATE_COLOR(_X) connectionDisplayStatus(0,0,_X)
#define LED_BT_COLOR(_X) connectionDisplayStatus(0,1,_X)

void clearDisplay();
void changeColor(int);
int drawchar(int, int,int, int);
void drawtext(int , int , char* ,int );
void scrollDisplay();
void connectionDisplayStatus(int , int , int );
