int arrayTx[SELECT][SIZEARRAY];

void serialWritting(int *high,int *low){
  for(int i=SIZEARRAY-1; i>=0 ;i--){

     digitalWrite(R1,(high[i]&1)!=0?1:0);
     digitalWrite(R2,(low[i]&1)!=0?1:0);    

     digitalWrite(G1,(high[i]&2)!=0?1:0);
     digitalWrite(G2,(low[i]&2)!=0?1:0);    
     
     digitalWrite(B1,(high[i]&4)!=0?1:0);
     digitalWrite(B2,(low[i]&4)!=0?1:0);    
     
     digitalWrite(SCLK_PIN,1);
     digitalWrite(SCLK_PIN,0); 
     delay(delayTime);
  }  
}
