long knobs[NumKnobs];
long knobsRelative[NumKnobs];
boolean knobChanged[NumKnobs];


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

