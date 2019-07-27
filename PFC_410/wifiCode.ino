#include <WiFi.h>
 
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
