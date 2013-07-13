byte relayPin[4] = {2,3,4,5};

//D2 -> COM1
//D3 -> COM2
//D4 -> COM3
//D5 -> COM4

void setup(){
  for(int i = 0; i < 4; i++)  pinMode(relayPin[i],OUTPUT);
}

// an sample to switch the 4 relays

void loop(){
  
  int i;
  for(i = 0; i < 4; i++)  digitalWrite(relayPin[i],HIGH);
  delay(1000);
  for(i = 0; i < 4; i++)  digitalWrite(relayPin[i],LOW);
  delay(1000);
 
}
