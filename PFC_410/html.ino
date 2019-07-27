#include <WiFi.h>
#include "ledMatrixDriver.h"

void sendPage(WiFiClient *client){
// send a standard http response header
  client->println("HTTP/1.1 200 OK");
  client->println("Content-Type: text/html");
  client->println("Connection: close"); // the connection will be closed after completion of the response
  client->println();
  client->println("<!DOCTYPE HTML><html><head>");
  client->println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
  client->println("<link rel=\"icon\" href=\"data:,\">");// escrito post favicon
  client->println("<h1>ESP32 - Web Server</h1>");
  client->println("<form action=\"\">");
  client->println("Linha1: <input type=\"text\" name=\"Linha1\" value=\"BABA\"><br>");
  client->println("Linha2: <input type=\"text\" name=\"Linha2\" value=\"Text\"><br>");
  client->println("<input type=\"submit\" value=\"Submit\">");
  //client->println("Cor Linha1: <input type=\"text\" name=\"Cor Linha1\" value=\"Text\"><br>");
  client->println("</form>");
  client->println("</html>");
}

boolean hasGet(char *buf){

  if (strstr(buf, "GET") == NULL){
      return false;
  }
    return true;    
}

void parseRequest(char *buf, WiFiClient *client){
    if(strcmp(buf, "GET / HTTP/1.1\r\n")){
        clearDisplay();    
        //Serial.printf(" Parsing %s", linebuf);
        char *param1 = strstr(buf, "Linha1=") + 7;
        char *param2 = strstr(buf, "Linha2=") + 7;

        char *end = strstr(param1, "&");
        *end = '\0';  // Terminador
        end = strstr(param2, " ");
        *end = '\0';

        Serial.printf("Parametro 1: %s\n", param1);
        Serial.printf("Parametro 2: %s\n", param2);
        drawtext(0,0,param1,7);
        drawtext(0,8,param2,2);
    }        
}
