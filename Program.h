//
// Light programs
//

// a program could be moving / color
// or combined. lights with more than one possible color are not supported at the moment.
//


#define MAX_PROGRAMS 10
#define MAX_PROGRAM_STEPS 10

#define RGB 1
#define HSV 2


boolean programRunning = true;

enum transistion{
  FADE_RGB,
  FADE_HSV,
  constant,
};

struct values{
  byte r;
  byte g;
  byte b;
  // HSV is calculated from RGB
  // Movement could be added also
};

struct programStep{
  struct values values;
  boolean colorType; // true=RGB,false=HSV
  unsigned int keepInMilliseconds;
  unsigned int durationInMilliseconds;
  byte lampSchema;
  enum transistion transistion;
  boolean phaseTroughLamps; // starts the program for each lamp in lampSchema delayed by 1/lamps
};

struct program{
  byte numberOfSteps;
  struct programStep steps[MAX_PROGRAM_STEPS];
};

struct programState{
  unsigned long stepStartMilliseconds;
  boolean keep;
  int currentStep;
};

struct programState programStates[MAX_PROGRAMS]={
  {0,true,0},
  {0,true,0}
};

struct program programs[MAX_PROGRAMS]={  // Demo program fade between Red and Blue 2&1 Second
    {
      3,        // Steps
      255,0,0,  //values
      RGB,     // RGB
      1500,     // keep duration before transistion
      2000,     // duration
      1,        // lamp schema
      FADE_RGB,  // fade
      0,        // phase delay
    
      0,255,255,
      RGB,
      1000,   
      1000,
      1,      
      FADE_RGB,
      0,

      0,0,255,
      RGB,   
      1000,
      1000,
      1,      
      FADE_RGB,
      0,
    }
};

unsigned long oldTime;

int getIntervalMS(){
  return 100;
};
bool checkProgramRunning(int number){
  return false;
};


void startProgram(){
  int number = 0;
//  checkProgramRunning(number);
  programStates[number].stepStartMilliseconds=millis();
  programStates[number].keep=true;
  programStates[number].currentStep=0;
  // Error: Conflict with running program
  programRunning=true;
  
};
void stopProgram(){
  programRunning=false;
};
void stopAllPrograms(){
  
};

byte mixValues(int color1, int color2,int percent){
  int mixed = ((color1*(100-percent))+(color2*percent))/200;
  return (byte)mixed;
};

RgbColor mixColorRGB(RgbColor color1,RgbColor color2,int percent){
  byte r = mixValues(color1.r,color2.r,percent);
  byte g = mixValues(color1.g,color2.g,percent);
  byte b = mixValues(color1.b,color2.b,percent);
}
RgbColor mixColorHSV(RgbColor color1,RgbColor color2,int percent){
  byte r = mixValues(color1.r,color2.r,percent);
  byte g = mixValues(color1.g,color2.g,percent);
  byte b = mixValues(color1.b,color2.b,percent);
}

byte nextStep(int programNumber, int programStep){
  byte nextProgramStep=programStep+1;
  if(nextProgramStep == programs[programNumber].numberOfSteps){
    nextProgramStep = 0;
  }
  return nextProgramStep;
}

void programExecutor(){
  if(programRunning==false){
    return;
  }

  byte percent;
  int programNumber = 0;
  int programStep = programStates[programNumber].currentStep;

  byte nextStepNumber=nextStep(programNumber,programStep);
  struct programStep thisStep = programs[programNumber].steps[programStep];
  struct programStep nextStep = programs[programNumber].steps[nextStepNumber];
  
// Just execute program 1
  unsigned long interval = millis()-programStates[programNumber].stepStartMilliseconds;
  unsigned int duration = thisStep.durationInMilliseconds;
  if(programStates[programNumber].keep==true){
    percent = 0;
    if(interval>thisStep.keepInMilliseconds){
      programStates[programNumber].stepStartMilliseconds=millis();
      programStates[programNumber].keep=false;
    }
  }else{
    percent = (long)interval*100L/duration;
    if(interval>duration){
      programStates[programNumber].stepStartMilliseconds=millis();
      programStates[programNumber].currentStep = nextStepNumber;
      programStates[programNumber].keep=true;
    }
  }

  // Calculate the color
  RgbColor colorFrom;
  RgbColor colorTo;
  RgbColor colorMixed;
  
  colorFrom.r = thisStep.values.r;
  colorFrom.g = thisStep.values.g;
  colorFrom.b = thisStep.values.b;

  colorTo.r = nextStep.values.r;
  colorTo.g = nextStep.values.g;
  colorTo.b = nextStep.values.b;
  
  switch(thisStep.transistion){
    case FADE_RGB:
      colorMixed = mixColorRGB(colorFrom,colorTo,percent);
      break;
    case FADE_HSV:
      colorMixed = mixColorHSV(colorFrom,colorTo,percent);
      break;
    default:
      colorMixed = colorFrom;
    break;
  };


  setDmxColor(0,colorMixed.r);
  setDmxColor(1,colorMixed.g);
  setDmxColor(2,colorMixed.b);

//  getRunningPrograms();

//  for(){
//    getValuesFromProgram()
//  }
}

