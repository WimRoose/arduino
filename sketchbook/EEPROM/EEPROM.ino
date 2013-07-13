#include <EEPROM.h>

char value;
char test[8]="testje";

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    //Serial.println("test");
    //Serial.println(test[i]);
    EEPROM.write(i, test[i]);
    delay(4);
   value = (char)EEPROM.read(i);

  
  Serial.print(value);
  

  
  }
   Serial.println();  
  delay(500);
}

void loop()
{
  
}
