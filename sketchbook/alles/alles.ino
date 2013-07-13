
#include <Time.h>  

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

String command; // String input from command prompt

char temp1,temp2; // temporary strings

int inByte; // Byte input from command prompt

char carray[6]; // character array for string to int // manipulation
int s;
int done=0;
int teller=0;
int a,b,c; // temporary numbers


void setup(){
 
    Serial.begin(9600);
    Serial.print("Akl");
    pinMode(13, OUTPUT);

}

void loop(){
  
  Serial.println (second());
  Serial.print(768);
  delay (1000);
  done = 0;
  int i=0;
  
  char commandbuffer[100];

  if(Serial.available()){

    delay(100);
    while( Serial.available() && i < 99) {
        commandbuffer[i++] = Serial.read();
    }
    //commandbuffer[i++]='\0';
  }
  
  
  
if (i > 0) {
  
      
  String serialInput =(char*)commandbuffer;
  
//Serial.println(serialInput);
 
  if (serialInput == "zet") {
    Serial.print("-OK");
    
  }
 if (serialInput == "zet\n") {
    Serial.print("-OK");
    
  } else {
    Serial.print("-NO");
    
    
    
  }
 
  
}
teller++;

}

   






