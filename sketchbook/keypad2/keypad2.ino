/*  Keypadtest.pde
 *
 *  Demonstrate the simplest use of the  keypad library.
 *
 *  The first step is to connect your keypad to the
 *  Arduino  using the pin numbers listed below in
 *  rowPins[] and colPins[]. If you want to use different
 *  pins then  you  can  change  the  numbers below to
 *  match your setup.
 *
 */
char serialBuffer[5];
byte countSerial = 0; 
 
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(44, 46, 47, 48, 49, 50);
#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 28, 26, 27, 29 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 24, 23, 22, 25 }; 

//byte rowPins[ROWS] = { 26, 27, 28, 29 };
//byte colPins[COLS] = { 22, 23, 24, 25 }; 

//byte rowPins[ROWS] = { 37, 36, 35, 34 };
//byte colPins[COLS] = { 33, 32, 31, 30 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledpin 13

void setup()
{
  pinMode(ledpin, OUTPUT);  
  digitalWrite(ledpin, LOW);
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Geef code in!");
}

void loop()
{
  //lcd.clear();
  //lcd.print("Geef code in!");
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '*':
        //digitalWrite(ledpin, LOW);
        Serial.print(key);
        break;
      case '#':
        //digitalWrite(ledpin, HIGH);
        //Serial.println();
        //Serial.print(key);
        checkCode();
        break;
      default:
        //digitalWrite(ledpin, LOW);
        Serial.print(key);
        
    }
  }
}



