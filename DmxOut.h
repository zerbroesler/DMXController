


#define dmxSize 10
#define dmxPin 22


#include <DmxSimple.h>

byte colors[][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
int col[3]={1,1,1};

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

void setDmxColor(int knob,byte value){
  int lamp = getLamp();
  col[knob]=(byte)value;
  if(lamp==0){
    int dmxStart=lamp*dmxSize;
    DmxSimple.write(dmxStart+1,0);
    DmxSimple.write(dmxStart+2,0);
    DmxSimple.write(dmxStart+3,255);
    DmxSimple.write(dmxStart+4,255);   // Master Dim
    DmxSimple.write(dmxStart+knob+5,value);
    // Calculate white
    int g  = col[1];
    int b  = col[2];
    int r  = col[0];
    if(knob==0){
    DmxSimple.write(dmxStart+8,200);
    }
    DmxSimple.write(dmxStart+5,r);
    DmxSimple.write(dmxStart+6,g);
    DmxSimple.write(dmxStart+7,b);

//    int m = (r<g)?r:g;//min(r,g);
//    int m = min(r,g);
//    int w = min(b,m);

//    byte w = b;//min(r,b);
//    int m;
//    if((int)r<(int)g){
//      m=0;
//    }else{
//      m=100;
//    }
//    DmxSimple.write(dmxStart+8,w);   // White
  }
  if(getLamp()==0){
    int dmxStart=getLamp()+1*dmxSize;
    DmxSimple.write(dmxStart+knob+1,value);
  }
}

