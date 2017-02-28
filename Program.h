//
// Light programs
//
// Lights with more than one possible color are not supported at the moment.
//

#define MAX_PROGRAMS 5
#define MAX_PROGRAM_STEPS 8

#define RGB 1
#define HSV 2

#define FADE_RGB 1
#define FADE_HSV 2
#define FADE_CONSTANT 3

boolean programRunning = true;

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
  byte transistion;
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

byte nextStep(int programNumber, int programStep){
  byte nextProgramStep=programStep+1;
  if(nextProgramStep == programs[programNumber].numberOfSteps){
    nextProgramStep = 0;
  }
  return nextProgramStep;
}

void programExecutor(){
  // Todo: Spagetthi coding
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
  byte lampNumber=0;
  setDmxColor(lampNumber,colorMixed);
  // Todo: How is the lamp shema stored within the program?
//  LampSchema lampSchema = getLampSchema(0);
//  for(byte i = 0;i<MAX_LAMPS;i++){
//    byte lampNumber=lampSchema.sequence[i];
//    if(lampNumber>0){
//      LampData lampData = getLampData(lampNumber);
//      if(lampData.active==true){
//        setDmxColor(lampNumber,colorMixed);
//      }
//    }
//  }
}

