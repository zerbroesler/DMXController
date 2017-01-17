// DMX Controller using a LCD Display for control
// 3 rotary encoders are used to control the values, push down for slow changes
// 1 rotary encoder is used to navigate through the menus, push down to select
// 


#include <Encoder.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DmxSimple.h>
// Project includes
#include "Display.h"

#define dmxPin 2
#define dmxChannel 1
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knob0(5, 4);
Encoder knob1(7, 6);
Encoder knob2(9, 8);
Encoder knob3(10,11);
//   avoid using pins with LEDs attached

#define NumKnobs 4
float positions[NumKnobs];
long  olds[NumKnobs];

void setup() {
  DmxSimple.usePin(dmxPin);
  DmxSimple.maxChannel(4);
  DmxSimple.write(dmxChannel,255);
//  pinMode(10,INPUT_PULLUP);
//  pinMode(11,INPUT_PULLUP);
//  pinMode(12,INPUT_PULLUP);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
//  Serial.begin(57600);
//  Serial.println("TwoKnobs Encoder Test:");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,2);
  lcd.print("Red   Green  Blue");
  for(int knob = 0;knob<NumKnobs;knob++){
    olds[knob]=1;
  }
}

boolean pressed = false;
char buf[3];
#define DISPLAYSPEED 3000
int  slowdisplay = DISPLAYSPEED;

void loop() {
  long news[NumKnobs];
  int menuentry = 0;
  news[0] = knob0.read();
  news[1] = knob1.read();
  news[2] = knob2.read();
  news[3] = knob3.read();

  // Menu
  
  if(slowdisplay == 0){

  if(news[3] != olds[3]){
    showLights((news[3]/4)%7+1);
    olds[3] = news[3];

    lcd.setCursor(2,1);
    lcd.print(olds[3]);      
  }

    
    
    showKnobs(news);
    slowdisplay = DISPLAYSPEED;
  }else{
    slowdisplay--;
  }
//    knobLeft.write(0);
//    knobRight.write(0);
}

void showKnobs(long news[]){
  for(int knob = 0;knob<3;knob++){
    if (news[knob] != olds[knob] ){
      if(analogRead(knob)>127){
        pressed = true;
      }else{
        pressed = false;
      }
      positions[knob] = calculateValue(positions[knob],news[knob]-olds[knob],pressed);
      showValue((int)positions[knob],knob*7+1);
      olds[knob] = news[knob];
      DmxSimple.write(dmxChannel+knob+1,(int)positions[knob]);
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
void showValue(long value,int pos){
//  int mil = millis();
  sprintf(buf,"%3u",value);
  lcd.setCursor(pos,3);
  lcd.print(buf);
//  showduration(mil);  
}

void showduration(int start){
  int mil = millis()-start;
  lcd.setCursor(2,2);
  lcd.print(mil);
}
void showLights(int selected){
  lcd.setCursor(0,0);
  lcd.print(" 1  2  3  4  5  6  7");
  if(selected>0){
    lcd.setCursor((selected-1)*3,0);
    lcd.print("*");
  }
}

