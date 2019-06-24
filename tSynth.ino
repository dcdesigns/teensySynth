#define PER_LOOP 30
#define HOLD_LOOPS 2000
#define DEAD_LOOPS 9000

#include <TeensyThreads.h>
#include <Arduino.h>
#include <Wire.h>
#include "synth/settings.h"
//#include "synth/PitchTables.c"
#include "synth/synthControls.h"
//#include "synth/midiHandler.h"
//#include "synth/fileLoader.h"
#include "synth/lcdLib.h"
//#include "synth/serialMidi.h"
//#include "synth/helperFunctions.c"





void inputChecker()
{

  while(1) 
  {
    handleKnobs();
    checkWriteElem();
    //threads.yield();    
  }
}

unsigned long lastTime;
void setup() {

  lastTime = micros();
  // put your setup code here, to run once:
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  screenInd = AMPENV;
  initSynthStuff();
  initLCD(); 
  Serial.write("Compiled");
  Serial.println();
  resetPatch();
  ticks = 0;
  threads.addThread(inputChecker);
  threads.setSliceMicros(1);
  
  int32_t full = 0x7fffffff;
  int32_t mult = full >> 1;
  float multf = (float)mult/full;
  int32_t val = 127;
  Serial.println((val ) * (multf));

}


void loop() {
  
  
  unsigned long startTime = micros();
  signed long elapsed = startTime - lastTime;
  if(elapsed < PER_LOOP)
  {
    delayMicroseconds(PER_LOOP - elapsed);
  }

  lastTime = micros();
  ticks++;
  scanInputs();
}
