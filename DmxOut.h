#include <DmxSimple.h>

byte colors[][3]={{1,0,0},{0,0,0},{0,0,0},{0,0,0}};

void dmxSetup(){
  DmxSimple.usePin(dmxPin);
  DmxSimple.maxChannel(81);
}

//void dmxWrite(){
//  int lampCount = getLampCount();
//  for(int lampNumber=0;lampNumber<lampCount;lampNumber++){
//    for(int dmxChannelNumber=0;dmxChannelNumber<dmxSize;dmxChannelNumber++){
//      DmxSimple.write(lampNumber+dmxChannelNumber,get);
//      
//    }
//    DmxSimple.write(lampNumber+2,0);
//    DmxSimple.write(lampNumber+3,0);
//  }
//}

void setDmxValue(int channel, int value){
  DmxSimple.write(getLamp()+channel+1,value);
}

void setDmxColor(int colorNumber,byte value){
  int lamp = getLamp();
  colors[lamp][colorNumber]=value;
  if(getLamp()==0){
    int dmxStart=lamp*dmxSize;
    DmxSimple.write(dmxStart+1,0);
    DmxSimple.write(dmxStart+2,0);
    DmxSimple.write(dmxStart+3,255);
    DmxSimple.write(dmxStart+4,255);   // Master Dim
//    DmxSimple.write(dmxStart+colorNumber+5,value);
    // Calculate white
    byte r  = colors[lamp][0];
    byte g  = colors[lamp][1];
    byte b  = colors[lamp][2];
    int w = min((int)b,min((int)r,(int)g));
    DmxSimple.write(dmxStart+8,w);   // White
    DmxSimple.write(dmxStart+5,r-w/2);
    DmxSimple.write(dmxStart+6,g-w/2);
    DmxSimple.write(dmxStart+7,b-w/2);
  }
//  if(getLamp()==0){
//    int dmxStart=getLamp()+1*dmxSize;
//    DmxSimple.write(dmxStart+knob+1,value);
//  }
}

