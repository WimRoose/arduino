void drawMatrices()  {
  
timeCount += 1;
  if(timeCount < 1000) {
    for (int i=0;i<8;i++) {
   
      updateShiftRegister1(drawLittleHeart[i]);
      updateShiftRegister2(drawLittleHeart[i]);
      updateShiftRegister3(drawLittleHeart[i]);
    
  }
  } else if (timeCount < 1200) {

  } else if (timeCount < 2000) {
    for (int i=0;i<8;i++) {
   
      updateShiftRegister1(drawLittleHeart2[i]);
      updateShiftRegister2(drawLittleHeart2[i]);
      updateShiftRegister3(drawLittleHeart2[i]);
    
  }
  } else if (timeCount < 2200) {
  // do nothing
  } else if (timeCount < 3000) {
    for (int i=0;i<8;i++) {
   
      updateShiftRegister1(drawLittleHeart3[i]);
      updateShiftRegister2(drawLittleHeart3[i]);
      updateShiftRegister3(drawLittleHeart3[i]);     
    
    }
  } else if (timeCount < 3200) {

  } else {
  // back to the start
  timeCount = 0;
}

}

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
