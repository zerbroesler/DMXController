#include <DmxSimple.h>


void dmxSetup(){
  DmxSimple.usePin(dmxPin);
  DmxSimple.maxChannel(81);
}

void setDmxValue(int channel, int value){
  DmxSimple.write(channel,value);
}


void setDmxRGB(int dmxStart,RgbColor color){

    byte r  = color.r;
    byte g  = color.g;
    byte b  = color.b;
    // Exponential color gradient as gamma correction
    r=(int)r*(int)r/255L;
    g=(int)g*(int)g/255L;
    b=(int)b*(int)b/255L;
    DmxSimple.write(dmxStart+1,r);
    DmxSimple.write(dmxStart+2,g);
    DmxSimple.write(dmxStart+3,b);
};

void setDmxRGBW(int dmxStart,RgbColor color){
    DmxSimple.write(dmxStart+1,0);
    DmxSimple.write(dmxStart+2,0);
    DmxSimple.write(dmxStart+3,255);
    DmxSimple.write(dmxStart+4,255);   // Master Dim
    // Calculate white
    byte r  = color.r;
    byte g  = color.g;
    byte b  = color.b;
    int w = min((int)b,min((int)r,(int)g));
    // Exponential color gradient as gamma correction
    w=(int)w*(int)w/255L;
    DmxSimple.write(dmxStart+8,w);   // White
    w/=2;
    RgbColor remainingColor;
    remainingColor.r = r-w;
    remainingColor.g = r-g;
    remainingColor.b = r-b;
    setDmxRGB(dmxStart+4,remainingColor);
};


void setDmxColor(byte lampNumber,RgbColor color){

  LampData lamp = getLampData(lampNumber);
  switch(lamp.dmxType){
  case 0:
	  setDmxRGBW(lamp.dmxAddress,color);
	  break;
  default:
	  setDmxRGB(lamp.dmxAddress,color);
	  break;
  }
   
};


