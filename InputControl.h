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
long olds[NumKnobs];
long news[NumKnobs];


void readKnobs(){
  news[0] = knob0.read();
  news[1] = knob1.read();
  news[2] = knob2.read();

  for(int knob = 0;knob<VALUEKNOBS;knob++){
    if (news[knob] != olds[knob] ){
      pressed = !digitalRead(pushpin[knob]);
      setKnobValue(knob,news[knob],news[knob]-olds[knob],pressed);
      olds[knob] = news[knob];
    }
  }
}

void readMenuKnob(){
  news[MENUKNOB] = knob3.read();
  if (news[MENUKNOB] != olds[MENUKNOB] ){
      setMenuValue(news[MENUKNOB]-olds[MENUKNOB]);
      olds[MENUKNOB] = news[MENUKNOB];
  }
  pressed = !digitalRead(pushpin[MENUKNOB]);
  setMenuPressed(pressed);
}


float calculateValue(float value,long difference,boolean press){
  if(press == false){
    value += difference / 4.0;
  }else{
    float multiply = abs((value+((float)difference)/1.5) / 30.0 + 0.5);
    
    value += difference * multiply;
  }
  if(value < 0){
    value = 0;
  }
  if(value > 255){
    value = 255;
  }
  return value;
}

