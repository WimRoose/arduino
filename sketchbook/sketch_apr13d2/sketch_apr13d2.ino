// Command line variables

String command; // String input from command prompt

char temp1,temp2; // temporary strings

int inByte; // Byte input from command prompt

char carray[6]; // character array for string to int // manipulation

int a,b,c; // temporary numbers

void setup(){

    Serial.begin(9600);

    Serial.println("hello th");

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
     Serial.println((char*)commandbuffer);
     
     
  String test =(char*)commandbuffer;
  if (test == "jupla") {
    Serial.println("allez ze");
    i=0
    ;
  }
    
  }
  
}

// if ((char*)commandbuffer == "test") {
  
//  Serial.println("doe toch es normaal!");
  
// }
  
   






