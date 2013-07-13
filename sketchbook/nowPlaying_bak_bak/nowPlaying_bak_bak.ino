// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int wim;
int pos;
char buffer[128];
char regeltotacht[7];
char staart[12];
String string;

void setup()
{
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  
  // Print a message to the LCD.
  //lcd.print("Yo man!");
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
      
        buffer[pos] = 0;
        lcd.clear();
        lcd.print("---starting");
        lcd.setCursor(0,2);
        lcd.print("--ok");
        memset(regeltotacht,0,sizeof(regeltotacht));
        for (int y=0;y<7;y++)  {
          regeltotacht[y] = buffer[y];
                    
        }
        //}
        string = (char*)regeltotacht;
        lcd.print
        (regeltotacht);
        Serial.println("regeltotacht");
        Serial.println(regeltotacht);
               
               
        memset(staart,0,sizeof(staart));
        for (int z=0;z<7;z++)  {
          staart[z] = buffer[z+7];
                    
        }
         string = (char*)staart;
        //}
        //lcd.setCursor(0,3);
        lcd.print(string);
        delay(1000);
        Serial.println(string);
           
      //lcd.print(staart);
      
      //lcd.setCursor(0,0);
      //Serial.println(buffer);
      pos = 0;
      //lcd.print(buffer);
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





   






