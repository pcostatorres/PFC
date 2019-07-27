BluetoothSerial SerialBT;

void connectUsingBT(){

//utilizar security code
//ssid + pass usar carater final com

  while(!SerialBT.hasClient());
  
  SerialBT.print("Credentials");

  switch (var){
    case S
  }
  int flag=0;
  while(flag!=2){
    if(SerialBT.available()){
      if(flag==0){
          //SerialBT.print("SSID");         
          String nom = SerialBT.readStringUntil('\n');
          int len = nom.length();
          nom.toCharArray(ssid , len);
          flag=1;
      }
      else if(flag==1){
          
          String nom2 = SerialBT.readStringUntil('\n');       
          int len = nom2.length();
          nom2.toCharArray(password , len);
          flag=2;
      }
    }
  }
  wifiBegin();
}
