
#define MAX_CHANNELS 15
#define MAX_CHANNEL_WRAP 13

int dmxAddress=0;
int dmxChannel=0;
// The values are only used when in this menu
// There is no persistency. They are updated to the DMX model after a change
byte dmxValues[MAX_CHANNELS];

void showDmxChannels(){
  // Show the correct channels as well as the values belonging to them
  showValue(dmxChannel+1,2,2);
  showValue(dmxChannel+2,8,2);
  showValue(dmxChannel+3,15,2);
}
void showDmxValues(){
  // Show the correct channels as well as the values belonging to them
  showValue(dmxValues[dmxChannel],1,3);
  showValue(dmxValues[dmxChannel+1],8,3);
  showValue(dmxValues[dmxChannel+2],15,3);
  setAbsoulteKnobValue(0,dmxValues[dmxChannel]);
  setAbsoulteKnobValue(1,dmxValues[dmxChannel+1]);
  setAbsoulteKnobValue(2,dmxValues[dmxChannel+2]);
}

void nextDmxAddress(){
  dmxAddress++;
  dmxAddress%=128;
}
void previousDmxAddress(){
  dmxAddress--;
  dmxAddress=(dmxAddress+128)%128;
}
void menuSpecialDmxAddressInit(){
  clearAround(0,1,5);
  showBrackets(6,1,3);
  showDmxChannels();
  showDmxValues();
}
void menuSpecialDmxAddress(){
  int relativeStep = getRelativeMenuStep();
  if(relativeStep==1){
    nextDmxAddress();
  }else if(relativeStep==-1){
    previousDmxAddress();
  }
  showValue(dmxAddress,7,1);

  if(getMenuPressed()==true){
    clearAround(6,1,3);
    showBrackets(0,1,5);
    setMenuSpecial(0);
  }
}

void menuSpecialDmxChannelInit(){
  // Angle brackets around the knob values to indicate that they can be shifted
  clearAround(10,1,8);
  showAngleBrackets(0,2,18);
}

void storeCurrentKnobs(){
  // Stores the selected knob values in the dmxValues array
  dmxValues[dmxChannel]=getKnobValue(0);
  dmxValues[dmxChannel+1]=getKnobValue(1);
  dmxValues[dmxChannel+2]=getKnobValue(2);
}
void updateDmxValues(){
  int start = dmxAddress+dmxChannel;
  setDmxValue(start,getKnobValue(0));
  setDmxValue(start+1,getKnobValue(1));
  setDmxValue(start+2,getKnobValue(2));
}


void nextDmxChannel(){
  storeCurrentKnobs();
  dmxChannel++;
  dmxChannel%=MAX_CHANNEL_WRAP;
  showDmxChannels();
  showDmxValues();
}

void previousDmxChannel(){
  storeCurrentKnobs();
  dmxChannel--;
  dmxChannel=(dmxChannel+MAX_CHANNEL_WRAP)%MAX_CHANNEL_WRAP;
  showDmxChannels();
  showDmxValues();
}

void menuSpecialDmxChannel(){
  int relativeStep = getRelativeMenuStep();
  if(relativeStep==1){
    nextDmxChannel();
    showDmxChannels();
  }else if(relativeStep==-1){
    previousDmxChannel();
    showDmxChannels();
  }
  updateDmxValues();
  if(getMenuPressed()==true){
    clearAround(0,2,18);
    showBrackets(10,1,8);
    setMenuSpecial(0);
  }
}
