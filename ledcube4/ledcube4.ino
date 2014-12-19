/*
  4x4x4 LED CUBE + Effects + Sound Analyzer
  =========================================
  © 2013 Elias Kuiter ( http://elias-kuiter.de )
*/

int modePin      =  2;
int shiftPin1    =  3; // data
int shiftPin2    =  4; // shift
int shiftPin3    =  5; // storage
int analyzerPin1 =  6; // strobe
int analyzerPin2 =  7; // RST
int analyzerPin3 = A0; // data

#include "Cube.h"
#include "FX.h"
#include "Audio.h"

#define LOOP   0
#define CLAP   1
#define VISUAL 2

#define DEBOUNCE 200

int mode = LOOP;
char modeChanged;
long time;
int previous;

void setup() {
  Serial.begin(9600);
  Cube::init_shifting(shiftPin1, shiftPin2, shiftPin3);
  //Cube::init(); // for use without shift registers
  Audio::init();
}

void loop() {
  modeChanged = false;
  switch (mode) {
    case LOOP:
      FX::loop();
      break;
    case CLAP:
      FX::clap();
      break;
    case VISUAL:
      FX::visual();
      break;
  }
}

void switchMode() {
  int modeChange = digitalRead(modePin);
  if (modeChange == true && previous == false && millis() - time > DEBOUNCE) {
    if (mode == VISUAL)
      mode = LOOP;
    else
      mode++;
    modeChanged = true;
    time = millis();    
  }
  previous = modeChange;
}
