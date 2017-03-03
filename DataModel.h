int knobs[NUMKNOBS]={0,0,0,0};
int knobsRelative[NUMKNOBS]={0,0,0,0};
long menuRelative = 0;
boolean knobChanged[NUMKNOBS]={true,true,true,true};
boolean menuPressed = false;
boolean menuReleased = false;
int knobMaximum=255;

int knobMode=0;

void setKnobsLinear(){
  knobMode = 1;
}
void setKnobsLogarithmic(){
  knobMode = 0;
}

void setKnobs100(){
  knobMaximum=100;
}
void setKnobs255(){
  knobMaximum=255;
}
int getKnobMaximum(){
  return knobMaximum;
}

int getKnobMode(){
  return knobMode;
}

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

