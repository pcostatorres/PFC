#include <WiFi.h>
#include "ledMatrixDriver.h"
 
// Replace with your network credentials
//char* ssid     = "MEO-8E93A0";
//char* password = "0cb4dc7f2b";

//const char* ssid     = "Paulo Neves";
//const char* password = "bx3w7zh5d1x0n";

//const char* ssid     = "Paulo Neves";
//const char* password = "ppssttoo";

char ssid[32];
char password[32];
 
 
// Client variables 

void wifiBegin(){
  
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.print("SSID ");                 
  Serial.println(ssid);
  Serial.print("Password "); 
  Serial.println(password); 
  WiFi.begin(ssid, password);
}

void wifiConexionInfo(WiFiServer *server){

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  server->begin();
  Serial.println(WiFi.localIP()); 
}

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

void wifiProcess(){

  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    memset(linebuf,0,sizeof(linebuf));
    int charcount=0;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) 
          {
              char c = client.read();
              //Serial.write(c);
              //read char by char HTTP request
              linebuf[charcount]=c;
              if (charcount < sizeof(linebuf)-1) 
                  charcount++;
   
              if (c == '\n' && currentLineIsBlank)
              {
                  sendPage(&client);
                  break;
              }
   
              if(c=='\n'){
                  currentLineIsBlank = true;
                  //Serial.printf("Comeca aqui", linebuf);
                  if(hasGet(linebuf)){
                      parseRequest(linebuf, &client);                
                  }
                  memset(linebuf,0,sizeof(linebuf));
              }
              else if (c != '\r')
              {
                  // you've gotten a character on the current line
                  currentLineIsBlank = false;
              }
          }
   
     scrollDisplay();
    }
    // give the web browser time to receive the data
    delay(1);
  
    client.stop();
    Serial.println("client disconnected");
      
    }
}
