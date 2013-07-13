
void updateShiftRegister1(int leds[2])
{
   /*digitalWrite(latchPin1, LOW);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[1]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[0]);
   digitalWrite(latchPin1, HIGH);*/
}
void updateShiftRegister2(int leds[2])
{
   digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, leds[1]);
    shiftOut(dataPin2, clockPin2, LSBFIRST, leds[0]);
   digitalWrite(latchPin2, HIGH);
}
void updateShiftRegister3(int leds[2])
{
   digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, leds[1]);
    shiftOut(dataPin3, clockPin3, LSBFIRST, leds[0]);
   digitalWrite(latchPin3, HIGH);
}
