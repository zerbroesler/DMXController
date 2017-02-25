int knobs[NUMKNOBS]={10,20,30,40};
int knobsRelative[NUMKNOBS]={0,0,0,0};
long menuRelative = 0;
boolean knobChanged[NUMKNOBS]={true,true,true,true};
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
  return knobs[knobNumber];
}
void setKnobChanged(int knobNumber, boolean changed){
  knobChanged[knobNumber]=false;
}

boolean getKnobChanged(int knobNumber){
  return knobChanged[knobNumber];
}

int getKnobValueLog(int knobNumber){
  long knobValue=knobs[knobNumber];
  knobChanged[knobNumber]=false;
  return (int)(knobValue*knobValue/255L);
}
void setAbsoulteKnobValue(int knobNumber,int absolute){
	knobs[knobNumber] = absolute;
}

int getRelativeForKnob(int knobNumber,long difference){
  int relative = 0;
//  Serial.println(difference);
  int knobRelative = knobsRelative[knobNumber]+difference;
  if(knobRelative>= 4){
    knobRelative -= 4;
    relative=1;
  }
  if(knobRelative <= -4){
    knobRelative += 4;
    relative=-1;
  }
  knobsRelative[knobNumber]=knobRelative;
  return relative;
}

void setKnobValue(int knobNumber,long difference,boolean pressed){
  int relative = getRelativeForKnob(knobNumber,difference);
  int value = knobs[knobNumber];
  if(pressed==false){
    value += ( relative*5 );
  }else{
    value += relative;
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

void setMenuRelative(long relative){
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

