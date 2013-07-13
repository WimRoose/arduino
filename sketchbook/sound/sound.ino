#include <Audio.h>
#include </home/lou/Desktop/sound.c>
void setup()
{
  // 44100Khz stereo => 88200 sample rate
  // 100 mSec of prebuffering.
  Audio.begin(44100, 100);
}

void loop()
{ 
  const int S=1024; // Number of samples to read in block
  short buffer[S];
  // no sine yet, just a ramp, within the 12 bits...
  for (short i = 0; i<S ; i++) {buffer[i]=i;}  
  // Audio.prepare(buffer, S, volume); not needed as values are 12 bits unsigned already 
  // Feed samples to audio
  Audio.write(buffer, S);

}
