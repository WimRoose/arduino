int piezo1=0;
int piezo2=1;
int piezo3=2;
int piezo4=3;
int piezo5=4;
int piezo6=5;
int piezo7;
int piezo8;
int piezo9;
int piezo10;
int piezo11;

void setup()  {
  
 Serial.begin(9600); 
  
}

void loop()  {
  

  int val1 = analogRead(piezo1);
  //Serial.println(val1);
  if (val1 > 50) {Serial.println("Knock_1");}
  int val2 = analogRead(piezo2);
  //Serial.println(val1);
  if (val2 > 50) {Serial.println("Knock_2");}
  int val3 = analogRead(piezo3);
  //Serial.println(val1);
  if (val3 > 50) {Serial.println("Knock_3");}
  int val4 = analogRead(piezo4);
  //Serial.println(val1);
  if (val4 > 50) {Serial.println("Knock_4");}
  int val5 = analogRead(piezo5);
  //Serial.println(val1);
  if (val5 > 50) {Serial.println("Knock_5");}
  int val6 = analogRead(piezo6);
  //Serial.println(val1);
  if (val6 > 50) {Serial.println("Knock_6");}
  int val7 = analogRead(piezo7);
  //Serial.println(val1);
  if (val7 > 50) {Serial.println("Knock_7");}
  int val8 = analogRead(piezo8);
  //Serial.println(val1);
  if (val8 > 50) {Serial.println("Knock_8");}
  int val9 = analogRead(piezo9);
  //Serial.println(val1);
  if (val9 > 50) {Serial.println("Knock_9");}
  int val10 = analogRead(piezo10);
  //Serial.println(val1);
  if (val10 > 50) {Serial.println("Knock_10");}
  int val11 = analogRead(piezo11);
  //Serial.println(val1);
  if (val11 > 50) {Serial.println("Knock_11");}
  
  
  delay(50);
  
}

