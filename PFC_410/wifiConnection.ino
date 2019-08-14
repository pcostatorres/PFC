#include <WiFi.h>
#include "matrixDriver.h"
#include "commands.h"

#define LENGTH_CREDENTIALS (EEPROM_SIZE/2)

// Replace with your network credentials
//char* ssid     = "SSIDMEO-8E93A0";
//char* password = "PASS0cb4dc7f2b";

char ssid[LENGTH_CREDENTIALS];
char password[LENGTH_CREDENTIALS];
char linebuf[80];
// Client variables 

int wifiBegin(int retries){
  
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.print("SSID ");                 
  Serial.println(ssid);
  Serial.print("Password "); 
  Serial.println(password); 
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while(WiFi.status() != WL_CONNECTED && retries>0){
    // Connect to WPA/WPA2 network.
    delay(500);
    Serial.print(".");
    retries--;
  } 
  return retries;
}

void wifiConnectionInfo(WiFiServer *server){
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  server->begin();
  Serial.println(WiFi.localIP()); 
  connectionDisplayStatus(0,1,1);
  connectionDisplayStatus(0,0,2);
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
  client->println("Linha1: <input type=\"text\" name=\"Linha1\" value=\"\"><br>");
  client->println("Linha2: <input type=\"text\" name=\"Linha2\" value=\"\"><br>");
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

void parseRequest(char *buf){
    if(strcmp(buf, "GET / HTTP/1.1\r\n")){
        clearDisplay();    
        int len = strlen(buf);
        char c = '?';

        parseCommands(chrInStr(buf,c,len), len);     
    }        
}

int wifiProcess(){

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Connection Lost!");
    return NCON;
  }
    
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
                      parseRequest(linebuf);                
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
    return WIFI;
}
