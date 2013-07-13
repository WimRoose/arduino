// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int pos;
char buffer[128];
String string;

void setup()
{
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("Yo man!");
  Serial.begin(9600);

  pos = 0;

  for (int i = 0; i < sizeof(buffer); i++)
    buffer[i] = 0;
}

void loop()
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  char c;
  char test;

  while (Serial.available() > 0) {
    c = Serial.read();
    
    if (c == ':') {
      buffer[pos] = 0;
      Serial.println(buffer);
      lcd.print (buffer);
      lcd.setCursor(0, 2);
    }
      
      if (c == '\n') {
      
        buffer[pos] = 0;
        Serial.println(buffer);
        lcd.clear();
        lcd.print ("    Now Playing");
        lcd.setCursor(0, 1);
        //test = (char)buffer[0];
        //if (&test == "t") {
          //lcd.setCursor(0, 2);
          lcd.print (buffer);
        //} else {
        //lcd.print(buffer);
        //}
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
  




   






