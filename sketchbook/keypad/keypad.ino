// How To Connect A Keypad To Arduino: Simple Example
// by Sebastian Tomczak 19 October 2011

// setup value for serial printing
byte value;

// setup pin names and numbers for cols and rows
byte row1 = 28;
byte row2 = 27;
byte row3 = 26;
byte row4 = 29;
byte col1 = 24;
byte col2 = 22;
byte col3 = 23;
byte col4 = 25;

 
void setup() {
Serial.begin(9600);

// setup row outputs
pinMode(row1, OUTPUT);
pinMode(row2, OUTPUT);
pinMode(row3, OUTPUT);
pinMode(row4, OUTPUT);

// setup col inputs
pinMode(col1, INPUT);
pinMode(col2, INPUT);
pinMode(col3, INPUT);
pinMode(col4, INPUT);

// setup internal resistors
digitalWrite(col1, HIGH);
digitalWrite(col2, HIGH);
digitalWrite(col3, HIGH);
digitalWrite(col4, HIGH);

// initialise rows
digitalWrite(row1, HIGH);
digitalWrite(row2, HIGH);
digitalWrite(row3, HIGH);
digitalWrite(row4, HIGH);
Serial.println("test");
}

void loop() {
// read row 1
digitalWrite(row1, LOW); // activate row 1
value = digitalRead(col1); // read row 1 & col 1 = button 1
if(value == 0) { // if the button is pressed...
Serial.println("Button 1 Pressed");
}
digitalWrite(row1, HIGH); // deactivate row 1

// repeat above for buttons 2 - 12 (i.e. rows 1 - 4 and cols 1 - 3)

digitalWrite(row1, LOW);
value = digitalRead(col2);
if(value == 0) {
Serial.println("Button 2 Pressed");
}
digitalWrite(row1, HIGH);


digitalWrite(row1, LOW);
value = digitalRead(col3);
if(value == 0) {
Serial.println("Button 3 Pressed");
}
digitalWrite(row1, HIGH);

digitalWrite(row1, LOW);
value = digitalRead(col4);
if(value == 0) {
Serial.println("Button A Pressed");
}
digitalWrite(row1, HIGH);

digitalWrite(row2, LOW);
value = digitalRead(col1);
if(value == 0) {
Serial.println("Button 4 Pressed");
}
digitalWrite(row2, HIGH);


digitalWrite(row2, LOW);
value = digitalRead(col2);
if(value == 0) {
Serial.println("Button 5 Pressed");
}
digitalWrite(row2, HIGH);


digitalWrite(row2, LOW);
value = digitalRead(col3);
if(value == 0) {
Serial.println("Button 6 Pressed");
}
digitalWrite(row2, HIGH);

digitalWrite(row2, LOW);
value = digitalRead(col4);
if(value == 0) {
Serial.println("Button B Pressed");
}
digitalWrite(row2, HIGH);

digitalWrite(row3, LOW);
value = digitalRead(col1);
if(value == 0) {
Serial.println("Button 7 Pressed");
}
digitalWrite(row3, HIGH);


digitalWrite(row3, LOW);
value = digitalRead(col2);
if(value == 0) {
Serial.println("Button 8 Pressed");
}
digitalWrite(row3, HIGH);


digitalWrite(row3, LOW);
value = digitalRead(col3);
if(value == 0) {
Serial.println("Button 9 Pressed");
}
digitalWrite(row3, HIGH);

digitalWrite(row3, LOW);
value = digitalRead(col4);
if(value == 0) {
Serial.println("Button C Pressed");
}
digitalWrite(row3, HIGH);

digitalWrite(row4, LOW);
value = digitalRead(col1);
if(value == 0) {
Serial.println("Button * Pressed");
}
digitalWrite(row4, HIGH);


digitalWrite(row4, LOW);
value = digitalRead(col2);
if(value == 0) {
Serial.println("Button 0 Pressed");
}
digitalWrite(row4, HIGH);


digitalWrite(row4, LOW);
value = digitalRead(col3);
if(value == 0) {
Serial.println("Button # Pressed");
}
digitalWrite(row4, HIGH);

digitalWrite(row4, LOW);
value = digitalRead(col4);
if(value == 0) {
Serial.println("Button D Pressed");
}
digitalWrite(row4, HIGH);

}
