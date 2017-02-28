#include <DmxSimple.h>


void dmxSetup(){
  DmxSimple.usePin(dmxPin);
  DmxSimple.maxChannel(81);
}

void setDmxValue(int channel, int value){
  DmxSimple.write(channel,value);
}


void setDmxRGBW(int dmxStart,RgbColor color){

    DmxSimple.write(dmxStart+1,0);
    DmxSimple.write(dmxStart+2,0);
    DmxSimple.write(dmxStart+3,255);
    DmxSimple.write(dmxStart+4,255);   // Master Dim
    // Calculate white
    byte r  = color.r;
    byte g  = color.g;
    byte b  = color.b;
    // Exponential color gradient as gamma correction
    r=(int)r*(int)r/255L;
    g=(int)g*(int)g/255L;
    b=(int)b*(int)b/255L;
    int w = min((int)b,min((int)r,(int)g));
    DmxSimple.write(dmxStart+8,w);   // White
    DmxSimple.write(dmxStart+5,r-w/2);
    DmxSimple.write(dmxStart+6,g-w/2);
    DmxSimple.write(dmxStart+7,b-w/2);
};


void setDmxColor(byte lampNumber,RgbColor color){

  LampData lamp = getLampData(lampNumber);
  setDmxRGBW(lamp.dmxAddress,color);
   
};


