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
  lcd.setCursor(0, 1);
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
        lcd.clear();
        lcd.print("Ook een goeiedag!");
      }
      else if (string == "lul") {
        Serial.println("Jij ook, kalf");
        lcd.clear();
        lcd.print("Jij ook, kalf");
      } 
      else {
        Serial.println("kversta u nieee");
        lcd.clear();
        lcd.print("kversta u nieee");
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
  




   






