#include "Arduino.h"
#include <Encoder.h>

Encoder knob0(5, 4);
Encoder knob1(7, 6);
Encoder knob2(9, 8);
Encoder knob3(10,11);
// Pins for Knob buttons
void inputSetup(){
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
}

boolean pressed = false;
long olds[NumKnobs];
long news[NumKnobs];


void readKnobs(){
  news[0] = knob0.read();
  news[1] = knob1.read();
  news[2] = knob2.read();
  news[3] = knob3.read();

  for(int knob = 0;knob<VALUEKNOBS;knob++){
    if (news[knob] != olds[knob] ){
      if(analogRead(knob)>127){
        pressed = true;
      }else{
        pressed = false;
      }
//      positions[knob] = calculateValue(positions[knob],news[knob]-olds[knob],pressed);
      setKnobValue(knob,news[knob]);
//      showValue((int)positions[knob],knob*7+1);
      olds[knob] = news[knob];
//      // Save values
//      DmxSimple.write(dmxChannel+knob+1,(int)positions[knob]);
    }
  }
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
