#include <DmxSimple.h>


void dmxSetup(){
  DmxSimple.usePin(dmxPin);
  DmxSimple.maxChannel(MAXCHANNEL);
}

void setDmxValue(int channel, int value){
  DmxSimple.write(channel,value);
}


void setDmxRGB(int dmxStart,RgbColor color){

    byte r  = color.r;
    byte g  = color.g;
    byte b  = color.b;
    // Exponential color gradient as gamma correction
//    r=(int)r*(int)r/255L;
//    g=(int)g*(int)g/255L;
//    b=(int)b*(int)b/255L;

    DmxSimple.write(dmxStart+0,r);
    DmxSimple.write(dmxStart+1,g);
    DmxSimple.write(dmxStart+2,b);
};

RgbwColor CalculateRgbw(RgbColor color){
    RgbwColor result;
    // Calculate white
    byte r  = color.r;
    byte g  = color.g;
    byte b  = color.b;
    int w = min((int)b,min((int)r,(int)g));
//    w/=2;
    result.w = w;
    result.r = r-w;
    result.g = g-w;
    result.b = b-w;
    return result;
}

void setDmxRGBW(int dmxStart,RgbColor color){
    RgbwColor rgbwColor = CalculateRgbw(color);
    RgbColor  remainingColor = RgbwToRgb(rgbwColor);
    DmxSimple.write(dmxStart+0,0);
    DmxSimple.write(dmxStart+1,0);
    DmxSimple.write(dmxStart+2,0);
    DmxSimple.write(dmxStart+3,255);   // Master Dim
    setDmxRGB(dmxStart+4,remainingColor);
    // Exponential color gradient as gamma correction
    byte w=(int)w*(int)w/255L;
    DmxSimple.write(dmxStart+7,rgbwColor.w);   // White
};
void setDmxRGBW2(int dmxStart,RgbColor color){
    RgbwColor rgbwColor = CalculateRgbw(color);
    RgbColor  remainingColor = RgbwToRgb(rgbwColor);
    DmxSimple.write(dmxStart+5,0);
    setDmxRGB(dmxStart,remainingColor);
    // Exponential color gradient as gamma correction
    byte w=(int)w*(int)w/255L;
    DmxSimple.write(dmxStart+3,rgbwColor.w);   // White
};




void setDmxColor(byte lampNumber,RgbColor color){

  LampData lamp = getLampData(lampNumber);
  switch(lamp.dmxType){
  case 0:
	  setDmxRGB(lamp.dmxAddress,color);
	  break;
  case 1:
    setDmxRGBW(lamp.dmxAddress,color);
    break;
  case 2:
    setDmxRGBW2(lamp.dmxAddress,color);
    break;
  default:
	  setDmxRGB(lamp.dmxAddress,color);
	  break;
  }
};

// DMX Merge
// Stores multiple DMX sets, merges them and passes to DmxSimple
//
// Is it possible to identify unchanged values?
// Idea: Initialize with 222 and use it as unchanged
// when 222 is stored, it is increased by 1 to secure special meaning of 222
// Since the high values have no visible difference this should not affect the visual impact
//
// bufferNumber can be 0 or 1
//
void clearDmxBuff(byte bufferNumber){
}

void mergeDmxBuffers(){
// Buffers are merged into buffer 0;  
}

void writeDmxBuffers(){
// Writes buffer 0 to DmxSimple  
}

void DmxProxy(int adress,byte value){
  // Just a proxy for Buffer/or DmxSimple
  // Could also check collisions for the same adress
  DmxSimple.write(adress,value);
}

