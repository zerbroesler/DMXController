// Display handling
// Also provides basic menu handling

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define DISPLAYSPEED 2000
#define VALUEKNOBS 3


long knobValues[NumKnobs];
void showKnobs();
char buf[3];

void displaySetup() {
//  Serial.begin(57600);
//  Serial.println("Debug:");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,2);
  lcd.print("Red   Green  Blue");


//  for(int knob = 0;knob<NumKnobs;knob++){
//    olds[knob]=1;
  //}

}

int  slowdisplay = DISPLAYSPEED;


void showValue(long value,int xpos,int ypos){
//  int mil = millis();
  sprintf(buf,"%3u",value);
  lcd.setCursor(xpos,ypos);
  lcd.print(buf);
//  showduration(mil);  
}

void showduration(int start){
  int mil = millis()-start;
  lcd.setCursor(2,2);
  lcd.print(mil);
}

void updateDisplay(){  
  if(slowdisplay == 0){
    showKnobs();
    slowdisplay = DISPLAYSPEED;
  }else{
    slowdisplay--;
  }
//    knobLeft.write(0);
//    knobRight.write(0);
}

void showKnobs(){

  int knobValue;
  for(int knob = 0;knob<VALUEKNOBS;knob++){
//     positions[knob] = calculateValue(positions[knob],news[knob]-olds[knob],pressed);
      if(getKnobChanged(knob)){
        knobValue = getKnobValueLog(knob);
        showValue(knobValue,knob*7+1,3);
        DmxSimple.write(dmxChannel+knob+1,knobValue);
      }
//      olds[knob] = news[knob];
//      // Save values
//    }
  }
}

// Proxies for other modules
void lcdSetCursor(int x, int y){
  lcd.setCursor(x,y);
}
void lcdPrint(String text){
  lcd.print(text);
}

