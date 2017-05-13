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
#include "Com.h"

enum mode { LOOP, CLAP, VISUAL, EFFECT };

#define DEBOUNCE 200

enum mode mode = LOOP;
char modeChanged;
long time;
int previous;
struct FX::effect_info* effect;

void setup() {
  Serial.begin(9600);
  Cube::init_shifting(shiftPin1, shiftPin2, shiftPin3);
  //Cube::init(); // for use without shift registers
  Audio::init();
  Com::init();
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
    case EFFECT:
      FX::run(effect->func, effect->options, effect->count);
      break;
  }
}

void switchMode() {
  int modeChange = digitalRead(modePin);
  if (modeChange == true && previous == false && millis() - time > DEBOUNCE) {
    if (mode == VISUAL || mode == EFFECT)
      mode = LOOP;
    else
      mode = (enum mode) ((int) mode + 1);
    modeChanged = true;
    time = millis();    
  }
  previous = modeChange;

  struct FX::effect_info* tmp_effect;
  if (Com::available()) {
    String cmd = Com::read();
    if (cmd == "loop")
      modeChanged = true, mode = LOOP;
    else if (cmd == "clap")
      modeChanged = true, mode = CLAP;
    else if (cmd == "visual")
      modeChanged = true, mode = VISUAL;
    else if ((tmp_effect = FX::to_effect(cmd)))
      effect = tmp_effect, modeChanged = true, mode = EFFECT;
    else
      Serial.println("command not recognized");
  }
}
