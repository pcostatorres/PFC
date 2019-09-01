int displayRGB [NLIN_MEM][NCOL_MEM];
int scroll_horizontal = 0;
int scroll_vertical = 0;
unsigned long timeStamp = 0;
int c = 1;


//colocar na matrixLed
void clearDisplay(){

  memset(displayRGB,0,sizeof(displayRGB));
  clearDisplayMatrix();
}

void changeColor(int color){

  for(int i=0;i<NLIN;i++){
    for(int j=0;j<NCOL;j++){

      displayRGB[i][j] = displayRGB[i][j] == 0?0:color;
    }
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
  updateDisplayMem(displayRGB, scroll_vertical,scroll_horizontal);
}

void scrollDisplay(){
  if(timeStamp<millis()){ 
      timeStamp = millis()+500;
      scroll_horizontal=scroll_horizontal==0?NCOL_MEM-NCOL:scroll_horizontal-1;
      scroll_horizontal=scroll_horizontal<0?NCOL_MEM-NCOL:scroll_horizontal;

      scroll_vertical=scroll_vertical==0?NLIN_MEM-NLIN:scroll_vertical-1;
      scroll_vertical=scroll_vertical<0?NLIN_MEM-NLIN:scroll_vertical;
      updateDisplayMem(displayRGB, scroll_vertical,scroll_horizontal);      
    }
}    

void connectionDisplayStatus(int x, int y, int color){

  displayRGB[x][y] = color;
  updateDisplayMem(displayRGB, scroll_vertical,scroll_horizontal);
}
