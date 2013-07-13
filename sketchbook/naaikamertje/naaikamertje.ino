

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int row=0;
int cTeller=0;
int pos;
char buffer[128];

void setup()
{
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  lcd.setCursor(0, row);
  
  
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
  
  char c;

  while (Serial.available() > 0) {
    c = Serial.read();
      
      if (c == '\n') {
        
        Serial.println(pos);
        buffer[pos] = 0;
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("Now Playing");
        row++;
        lcd.setCursor(0,row);
        for (int i=0;i<pos;i++)  {
        
           if (cTeller == 20) {
             row++;          
             lcd.setCursor(0,row);
             Serial.println("->>20");
             cTeller = 0;
           }
           //if (i == 40) {          
           //  lcd.setCursor(0,2); 
           //  Serial.println("->>40");
           //}
           if (buffer[i] == ':')  {
            row++;
            lcd.setCursor(0,row);
            i++;
            cTeller=0;
           }
           lcd.print(buffer[i]);
           cTeller++;       
        }
        row=0;
        cTeller = 0;
        pos = 0;
  
      for (int i = 0; i < sizeof(buffer); i++)
    buffer[i] = 0;
}
    else {
      buffer[pos] = c;
      
      pos++;
      
      

      if (pos >= sizeof(buffer)) {
        pos = 0;
      }
      
    }
      
  }
    
    
}





   






