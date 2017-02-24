
int dmxAddress;
int dmxChannel;

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

void nextDmxChannel(){
  dmxChannel++;
  dmxChannel%=32;
}

void previousDmxChannel(){
  dmxChannel--;
  dmxChannel=(dmxChannel+32)%32;
}
void menuSpecialDmxChannelInit(){
  clearAround(0,1,5);
  showBrackets(6,1,3);
}

void showDmxChannels(){
  // Show the correct channels as well as the values belonging to them  
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

