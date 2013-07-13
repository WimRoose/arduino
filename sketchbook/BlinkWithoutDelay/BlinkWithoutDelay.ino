int Pin = 2;
int ledPin = 13; // LED connected to digital pin 13

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(Pin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);   // sets the LED on
  digitalWrite(Pin, HIGH);
  delay(1000); 
    // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  digitalWrite(Pin, LOW);
  delay(1000);                  // waits for a second
}
