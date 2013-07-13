
char hits[4][3];
char boks[4][3];
char een[3]="01";
char twee[3]="26";
char drie[3]="45";
int potPin = 2;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor


void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  strcpy ( hits[0], een );
  strcpy ( hits[1], twee );
  strcpy ( hits[2], drie);
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  
}

void loop()
{
 
  for (int i=0;i<3;i++)  {
    
    Serial.println(hits[i]);
    val = analogRead(potPin);    // read the value from the sensor
    
    Serial.println(valToBoks(val));
    //Serial.print(hits[i][i+1]);
    delay(1000);
    
  }
  /*
  char inByte = 0;
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    
    // byte read, send three characters
    Serial.print("J");
    Serial.print("A");
    Serial.print("!");
       
  }
  */
}
char* valToBoks(int value) {

static char toBoks[3];
   
   if (value<10)  {
    
      toBoks[0]='0';
      toBoks[1]=(char)value;
         }
   else if (value < 100) {
         itoa(value, toBoks, 10);
   }
   else {
        itoa(value, toBoks, 10);   
   }
 
 return toBoks; 
}


