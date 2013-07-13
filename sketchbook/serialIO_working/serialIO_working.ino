int pos;
char buffer[128];
String string;

void setup()
{
  Serial.begin(9600
  );

  pos = 0;

  for (int i = 0; i < sizeof(buffer); i++)
    buffer[i] = 0;
}

void loop()
{
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
      }
      else if (string == "lul") {
        Serial.println("Jij ook, kalf");
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
  




   






