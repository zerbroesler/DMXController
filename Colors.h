typedef struct RgbColor
{
    byte r;
    byte g;
    byte b;
} RgbColor;

typedef struct RgbwColor
{
    byte r;
    byte g;
    byte b;
    byte w;
} RgbwColor;

typedef struct HsvColor
{
    byte h;
    byte s;
    byte v;
} HsvColor;

RgbColor RgbwToRgb(RgbwColor colorIn){
  return {colorIn.r,colorIn.g,colorIn.b};
}

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    byte region, p, q, t;
    unsigned int h, s, v, remainder;

    if (hsv.s == 0)  // grey
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    // converting to 16 bit to prevent overflow
    h = hsv.h%256;
    s = hsv.s;
    v = hsv.v;

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = v;
            rgb.g = t;
            rgb.b = p;
            break;
        case 1:
            rgb.r = q;
            rgb.g = v;
            rgb.b = p;
            break;
        case 2:
            rgb.r = p;
            rgb.g = v;
            rgb.b = t;
            break;
        case 3:
            rgb.r = p;
            rgb.g = q;
            rgb.b = v;
            break;
        case 4:
            rgb.r = t;
            rgb.g = p;
            rgb.b = v;
            break;
        default:
            rgb.r = v;
            rgb.g = p;
            rgb.b = q;
            break;
    }
    return rgb;
}

HsvColor RgbToHsv(RgbColor rgb)
{
    HsvColor hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.v = rgbMax;
    if (hsv.v == 0)  // black
    {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * ((long)(rgbMax - rgbMin)) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}

byte mixValues(int color1, int color2,int percent){
  int mixed = ((color1*(100-percent))+(color2*percent))/100;
  return (byte)mixed;
};
byte mixValuesLow(int color1, int color2,int percent){
  int fastPercent = percent * 3 / 2;
  int percent1 = (100 - fastPercent);
  int percent2 = (fastPercent -50 );
  if(percent1 < 0){
    percent1 = 0;
  };
  if(percent2 < 0){
    percent2 = 0;
  };
  int mixed = ((color1*percent1)+(color2*percent2))/100;
  return (byte)mixed;
};

RgbColor mixColorRGB(RgbColor color1,RgbColor color2,int percent){
  byte r = mixValues(color1.r,color2.r,percent);
  byte g = mixValues(color1.g,color2.g,percent);
  byte b = mixValues(color1.b,color2.b,percent);
  RgbColor mixed = {r,g,b};
  return mixed;
};
RgbColor mixColorRGBLow(RgbColor color1,RgbColor color2,int percent){
  // Similar as mixColorRGB, but is almost black in between
  byte r = mixValuesLow(color1.r,color2.r,percent);
  byte g = mixValuesLow(color1.g,color2.g,percent);
  byte b = mixValuesLow(color1.b,color2.b,percent);
  RgbColor mixed = {r,g,b};
  return mixed;
};


RgbColor mixColorHSV(RgbColor color1,RgbColor color2,int percent){
  HsvColor hsv1 = RgbToHsv(color1);
  HsvColor hsv2 = RgbToHsv(color2);
  HsvColor hsvResult;
  int h1 = hsv1.h; // Need a bigger range
  int h2 = hsv2.h; // since hue is circular, we also want to go in both directions

//  if(h2-h1>127){
//    h1+=256;
//  }
  if(h1-h2>127){
    h2+=256;
  }
  
  hsvResult.h = mixValues(h1,h2,percent);
  hsvResult.s = mixValues(hsv1.s,hsv2.s,percent);
  hsvResult.v = mixValues(hsv1.v,hsv2.v,percent);
  return HsvToRgb(hsvResult);
};

