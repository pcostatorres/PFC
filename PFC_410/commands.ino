#define POS_LINE_HIGH(_V, _C) drawtext(0,0,_V,_C); 
#define POS__LINE_LOW(_V, _C) drawtext(0,8,_V,_C); 

char *extractParameterValue(char *query, char *param, char *value, char len){
  char *ptr;
  char i;

  if(query == NULL || param == NULL || value == NULL)
    return NULL;
  // Find param
  ptr = strstr(query, param);
  if(ptr == NULL || ptr >= query + len )
    return NULL;

  // skip param
  while(*ptr++ != '='){
    if(ptr == query + len)
      return NULL;
  } 
  // copy value
  i = 0;
  while(*ptr != '&' && *ptr != '#' && *ptr != ' ' && ptr != query + len){
    *(value + i++) = *ptr++;
  }
  // end string
  *(value + i) = '\0';
  return value;
}

void parseCommands(char* buf, int len){

  char value[len];
  int cor1 = RED;
  int cor2 = RED;
  
  if(extractParameterValue(buf,"Cor1",value,len)!=NULL){  
    cor1 = atoi(value);
  }
    
  if(extractParameterValue(buf,"Cor2",value,len)!=NULL){  
    cor2 = atoi(value);
  }
  
  if(extractParameterValue(buf,"Linha1",value,len)!=NULL){  
    POS_LINE_HIGH(value, cor1);
  }
  
  if(extractParameterValue(buf,"Linha2",value,len)!=NULL){  
    POS__LINE_LOW(value, cor2)
  }
}

char *chrInStr(char *str, char c, char len) {
  if (str == NULL) return 0;
  while (*str) {
    if (*str == c)
      break;
    str += 1;
    if((--len) == 0)
      return NULL;
  }
  return str;
}
