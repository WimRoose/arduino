
//LEDMATRIX 1 - HARTJES
void updateShiftRegister1(int leds[2])
{
   digitalWrite(latchPin1, LOW);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[1]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, leds[0]);
   digitalWrite(latchPin1, HIGH);
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

//LEDMATRIX 2 - POWER METER

void updateShiftRegister6(int leds[2])
{
   digitalWrite(latchPin6, LOW);
    shiftOut(dataPin6, clockPin6, LSBFIRST, leds[1]);
    shiftOut(dataPin6, clockPin6, LSBFIRST, leds[0]);
   digitalWrite(latchPin6, HIGH);
}
void updateShiftRegister7(int leds[2])
{
   digitalWrite(latchPin7, LOW);
    shiftOut(dataPin7, clockPin7, LSBFIRST, leds[1]);
    shiftOut(dataPin7, clockPin7, LSBFIRST, leds[0]);
   digitalWrite(latchPin7, HIGH);
}
void updateShiftRegister8(int leds[2])
{
   digitalWrite(latchPin8, LOW);
    shiftOut(dataPin8, clockPin8, LSBFIRST, leds[1]);
    shiftOut(dataPin8, clockPin8, LSBFIRST, leds[0]);
   digitalWrite(latchPin8, HIGH);
}
