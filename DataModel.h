long knobs[NumKnobs];
long menuRelative = 0;
boolean knobChanged[NumKnobs]={true,true,true};
boolean menuPressed = false;
boolean menuReleased = false;
//byte dmxValues[][10];
int lampCount=2;
int lampNumber=0;

struct LampData{
	bool active;     // On or off
	int  dmxAddress; //
	int  dmxType;
};
LampData lampsData[] = {
  // Temporary until ui config exists
	{true,1,0},
	{true,11,0},
	{false,21,0},
};


long getKnobValue(int knobNumber){
  knobChanged[knobNumber]=false;
  return knobs[knobNumber];
}

boolean getKnobChanged(int knobNumber){
  return knobChanged[knobNumber];
}

int getKnobValueLog(int knobNumber){
  knobChanged[knobNumber]=false;
  return (int)(knobs[knobNumber]*knobs[knobNumber]/255);
}

void setKnobValue(int knobNumber,int relative,boolean pressed){
  int value = knobs[knobNumber]+relative;
  if(pressed==false){
    value += relative*2;
  }
  if(value < 0){
    value = 0;
  }
  if(value > 255){
    value = 255;
  }
  knobs[knobNumber] = value;
  knobChanged[knobNumber]=true;
}

void setMenuValue(long relative){
  menuRelative+=relative;
}

long getMenuRelative(){
  return menuRelative;
}

void setMenuPressed(bool pressed){
  // Only set pressed when the button was released
  // between two calles of setMenuPressed
  if(pressed == true ){
    if(menuReleased == true ) {
      menuPressed = true;
      menuReleased = false;
    }
  }else{
    menuReleased = true;
  }
}

bool getMenuPressed(){
  bool wasPressed = menuPressed;
  menuPressed = false;
  return wasPressed;
}

void setLampCount(int count){
  lampCount = count;
}
int getLampCount(){
  return lampCount;
}

void setLamp(int number){
  lampNumber = number;
}
int getLamp(){
  return lampNumber;  
}

//void setDmxValue(int channel, int value){
//  dmxValues[lampNumber][channel] = value;  
//}
//void getDmxValue(int channel){
//  return dmxValues[lampNumber][channel];
//}

