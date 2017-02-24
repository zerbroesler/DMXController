// Display handling
// Also provides basic menu handling

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


void showKnobs();

void displaySetup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,2);
  lcd.print("Red   Green  Blue");
}

int  slowdisplay = DISPLAYSPEED;


void showValue(long value,int xpos,int ypos){
//  int mil = millis();
  char buf[3];
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

void updateKnobs(){
  if(slowdisplay == 0){
    showKnobs();
    slowdisplay = DISPLAYSPEED;
  }else{
    slowdisplay--;
  }
}

void showKnobs(){

  int knobValue;
  for(int knob = 0;knob<VALUEKNOBS;knob++){
      if(getKnobChanged(knob)){
        knobValue = getKnobValueLog(knob);
        // Todo: Move setDmxColor to test and make the showValue configurable
        showValue(knobValue,knob*7+1,3);
        setDmxColor(knob,knobValue);
      }
  }
}

// Proxies for other modules
void lcdSetCursor(int x, int y){
  lcd.setCursor(x,y);
}
void lcdPrint(String text){
  lcd.print(text);
}

