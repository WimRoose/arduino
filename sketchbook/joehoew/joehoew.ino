// Command line variables

String command; // String input from command prompt

char temp1,temp2; // temporary strings

int inByte; // Byte input from command prompt

char carray[6]; // character array for string to int // manipulation

int a,b,c; // temporary numbers

void setup(){

    
  
    Serial.begin(9600);

    Serial.println("Arduinoman is klaar!");
    pinMode(13, OUTPUT);
    //digitalWrite(13, LOW);
    

}

void loop(){

   int i=0;
  char commandbuffer[100];

  if(Serial
  .available()){
     delay(100);
     while( Serial.available() && i< 99) {
        commandbuffer[i++] = Serial.read();
     }
     commandbuffer[i++]='\0';
  }

  if(i>0) {
     //Serial.println((char*)commandbuffer);
     
     
  String test =(char*)commandbuffer;
  if (test == "hallo") {
    Serial.println("Hallooo! Eindelijk iemand om mee te praten!");
    i=0
    ;
  }
  if (test == "alles goed?") {
    Serial.println("Ja hoor, ik wacht op uitbreiding :-)");
    i=0
    ;
  }
  if (test == "led on") {
    Serial.println("licht aan!");
    digitalWrite(13, HIGH);   // set the LED on
    i=0
    ;
  }
  if (test == "led off") {
    Serial.println("licht uit!");
    digitalWrite(13, LOW);   // set the LED on
    i=0
    ;
  }
  
    
  }
  
}

// if ((char*)commandbuffer == "test") {
  
//  Serial.println("doe toch es normaal!");
  
// }
  
   






