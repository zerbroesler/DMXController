long knobs[NumKnobs];
long knobsRelative[NumKnobs];
long menuRelative = 0;
boolean knobChanged[NumKnobs];
boolean menuPressed = false;
boolean menuReleased = false;

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

void setKnobValue(int knobNumber,long value,long relative,boolean pressed){
  value -= knobsRelative[knobNumber];
  if(pressed==false){
    value += relative*2;
    knobsRelative[knobNumber] -= relative*2;
  }
  if(value < 0){
    knobsRelative[knobNumber] += value;
    value = 0;
  }
  if(value > 255){
    knobsRelative[knobNumber] += value-256;
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

