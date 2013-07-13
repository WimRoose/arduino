


/*
 * Switch test program
 */


int switchPin = 
2;
int ledPin = 3;
int val;
int swits = 0;
int light = 0;
int lightSensor = 5;
int light_val;
int moistSensor = 4;
int moist_val;


void setup()                    // run once, when the sketch starts
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  pinMode(switchPin, INPUT);  // sets the digital pin as input to read switch
  pinMode(ledPin, OUTPUT);
}


void loop()                     // run over and over again
{
  //Serial.print("Read switch input: ");
  //val = digitalRead(switchPin);  // Read the pin and display the value
  //Serial.println(val);
  //if (val == 0)  {swits=0;}
  //if ((val != 0) && (swits != 1)) {
  
    //swits = 1;
    //Serial.println("Button pressed!\n");
    
   // if (light == 0)  {
     // digitalWrite(ledPin, HIGH);
      //light = 1;
    //} else {
    
      //digitalWrite(ledPin, LOW);
      //light = 0;
      
   // }
  //
//}
  light_val = analogRead(lightSensor); // read the value from the photosensor
  Serial.print("light sensor reads ");
  
  Serial.println( light_val );
  if (light_val < 450)  {
      digitalWrite(ledPin, HIGH);
      
  }
  if (light_val > 450)
  {
      digitalWrite(ledPin, LOW);
      
  }
  
  moist_val = analogRead(moistSensor); // read the value from the photosensor
  Serial.print("moist sensor reads ");
  
  Serial.println( moist_val );
   
  delay(1000);
    
}
