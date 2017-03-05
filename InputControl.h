#include "Arduino.h"
#include <Encoder.h>

#define PUSH_0 30
#define PUSH_1 34
#define PUSH_2 38

// Left, Middle, Right below display
Encoder knob0(28, 2);
Encoder knob1(32,18);
Encoder knob2(36,19);
// Push down on knobs

// Big Selector
Encoder knob3(3, 24);
// Push down
#define PUSH_3 26
#define BACK3 40  // Button next to the selector to go back
#define MENUKNOB 3
int pushpin[4]={PUSH_0,PUSH_1,PUSH_2,PUSH_3};

// Pins for Knob buttons
void inputSetup(){
  pinMode(PUSH_0,INPUT_PULLUP);
  pinMode(PUSH_1,INPUT_PULLUP);
  pinMode(PUSH_2,INPUT_PULLUP);
  pinMode(PUSH_3,INPUT_PULLUP);
  pinMode(BACK3,INPUT_PULLUP);
}

boolean pressed = false;
// For relative
long olds[NUMKNOBS];
long news[NUMKNOBS];


void readKnobs(){
  news[0] = knob0.read();
  news[1] = knob1.read();
  news[2] = knob2.read();

  for(int knob = 0;knob<VALUEKNOBS;knob++){
    if (news[knob] != olds[knob] ){
      pressed = !digitalRead(pushpin[knob]);
      setKnobValue(knob,news[knob]-olds[knob],pressed);
      olds[knob] = news[knob];
    }
  }
}

void readMenuKnob(){
  news[MENUKNOB] = knob3.read();

  if (news[MENUKNOB] != olds[MENUKNOB] ){
      setMenuRelative(news[MENUKNOB]-olds[MENUKNOB]); 
      olds[MENUKNOB] = news[MENUKNOB];
  }
  pressed = !digitalRead(pushpin[MENUKNOB]);
  setMenuPressed(pressed);
}

