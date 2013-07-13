int pos;
char buffer[128];
String string;
int Pin = 12;
int ledPin = 13; // LED connected to digital pin 13


void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(Pin, OUTPUT);
  Serial.begin(9600
  );

  pos = 0;

  for (int i = 0; i < sizeof(buffer); i++)
    buffer[i] = 0;
}

void loop()
{
  delay(100);
  char c;

  while (Serial.available() > 0) {
    c = Serial.read();

    if (c == '\n' || c == ':') {
      buffer[pos] = 0;
      Serial.print("\nArduino received: ");
      //Serial.print(pos);
      Serial.println(buffer);
      string = (char*)buffer;
      if (string == "Daag") {
        Serial.println("Ook een goeiedag!");
        digitalWrite(ledPin, HIGH);   // sets the LED on
        digitalWrite(Pin, HIGH);
      }
      else if (string == "lul") {
        Serial.println("Jij ook, kalf");
        digitalWrite(ledPin, LOW);    // sets the LED off
        digitalWrite(Pin, LOW);
      } 
      else {
        Serial.println("kversta u nieee");
      }
      pos = 0;
    }
    else {
      buffer[pos] = c;
      pos++;
      

      if (pos >= sizeof(buffer))
        pos = 0;
    }
  }
}
  




   






