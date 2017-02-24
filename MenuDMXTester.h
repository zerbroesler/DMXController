
#define MAX_CHANNELS 15
#define MAX_CHANNELS_VISIBLE MAX_CHANNELS-2

int dmxAddress;
int dmxChannel;
// The values are only used when in this menu
// There is no persistency. They are updated to the DMX model after a change
byte dmxValues[MAX_CHANNELS];


void nextDmxAddress(){
  dmxAddress++;
  dmxAddress%=128;
}
void previousDmxAddress(){
  dmxAddress--;
  dmxAddress=(dmxAddress+128)%128;
}
void menuSpecialDmxAddressInit(){
  // Angle brackets around the knob values to indicate that they can be shifted
  clearAround(10,1,8);
  showAngleBrackets(0,2,18);
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
  clearAround(0,1,5);
  showBrackets(6,1,3);
}

void showDmxChannels(){
  // Show the correct channels as well as the values belonging to them
  showValue(dmxChannel,2,2);
  showValue(dmxChannel+1,8,2);
  showValue(dmxChannel+2,15,2);
}
void showDmxValues(){
  // Show the correct channels as well as the values belonging to them
  showValue(dmxValues[dmxChannel],2,3);
  showValue(dmxValues[dmxChannel+1],8,3);
  showValue(dmxValues[dmxChannel+2],15,3);
}
void nextDmxChannel(){
  dmxChannel++;
  dmxChannel%=MAX_CHANNELS_VISIBLE;
  showDmxChannels();
  showDmxValues();
}

void previousDmxChannel(){
  dmxChannel--;
  dmxChannel=(dmxChannel+MAX_CHANNELS_VISIBLE)%MAX_CHANNELS_VISIBLE;
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
  if(getMenuPressed()==true){
    clearAround(0,2,18);
    showBrackets(10,1,8);
    setMenuSpecial(0);
  }
}
