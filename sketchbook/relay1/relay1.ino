byte relayPin=4;

//D2 -> COM1
//D3 -> COM2
//D4 -> COM3
//D5 -> COM4

void setup(){
  pinMode(relayPin,OUTPUT);
}

// an sample to switch the 4 relays

void loop(){
  
  digitalWrite(relayPin,HIGH);
  delay(1000);
  digitalWrite(relayPin,LOW);
  delay(1000);
 
}
