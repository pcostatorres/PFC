char *extractParameterValue(char *query, char *param, char *value, char len){
  char *ptr;
  char i;

  //Serial.println(query);
  if(query == NULL || param == NULL || value == NULL)
    return NULL;
  // Find param
  ptr = strstr(query, param);
  //Serial.println(ptr);
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
  int cor1 = DEFAULTCOLOR;
  int cor2 = DEFAULTCOLOR;
  
  if(extractParameterValue(buf,"Cor1",value,len)!=NULL){  
    cor1 = atoi(value);
    Serial.println(buf);
  }
    
  if(extractParameterValue(buf,"Cor2",value,len)!=NULL){  
    cor2 = atoi(value);
    Serial.println(buf);
  }
  
  if(extractParameterValue(buf,"Linha1",value,len)!=NULL){  
    drawtext(0,0,value,cor1);  
    Serial.println(buf);
  }
  
  if(extractParameterValue(buf,"Linha2",value,len)!=NULL){  
    drawtext(0,8,value,cor2);
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
