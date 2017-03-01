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
int programSpeedStep=0;
unsigned long globalProgramStart=0;

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

struct stepState{
  byte percent;
  byte stepNumber;
  boolean keep;
};

struct programState{
  unsigned long programDuration;
  unsigned long stepStartMilliseconds;
  boolean keep;
  int currentStep;
};

struct programState programStates[MAX_PROGRAMS]={
  {0,0,true,0},
  {0,0,true,0}
};

struct program programs[MAX_PROGRAMS]={  // Demo program fade between Red and Blue 2&1 Second
    {
      3,        // Steps
      50,0,0,  //values
      RGB,     // RGB
      5000,     // keep duration before transistion
      4000,     // duration
      1,        // lamp schema
      FADE_RGB,  // fade
      0,        // phase delay
    
      0,0,80,
      RGB,
      5000,   
      4000,
      1,      
      FADE_RGB,
      0,

      0,60,0,
      RGB,   
      5000,
      4000,
      1,      
      FADE_RGB,
      0,
    },{
      0
    },{
      0
    },{
      0
    },{
      0
    }
};

bool checkProgramRunning(int number){
  return false;
};

unsigned long calculateProgramDuration(int programNumber){
  unsigned long programDuration=0;
  for(int i=0;i<programs[programNumber].numberOfSteps;i++){
    programDuration+=programs[programNumber].steps[i].keepInMilliseconds;
    programDuration+=programs[programNumber].steps[i].durationInMilliseconds;    
  }
  return programDuration;
}

void rememberAllProgramsDurations(){
  for(int i = 0;i<MAX_PROGRAMS;i++){
    programStates[i].programDuration = calculateProgramDuration(i);
  }
}

void startProgram(){
  int number = 0;
  rememberAllProgramsDurations();
  globalProgramStart = millis();
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

boolean reduceCalls(){
  programSpeedStep++;
  if(programSpeedStep<PROGRAMSPEED){
    return false;
  }else{
    programSpeedStep=0;
    return true;
  }
}

struct RgbColor mixColorsOfSteps(programStep *thisStep, programStep *nextStep,int percent){

  RgbColor colorFrom;
  RgbColor colorTo;
  RgbColor colorMixed;
  
  colorFrom.r = thisStep->values.r;
  colorFrom.g = thisStep->values.g;
  colorFrom.b = thisStep->values.b;

  colorTo.r = nextStep->values.r;
  colorTo.g = nextStep->values.g;
  colorTo.b = nextStep->values.b;
  
  switch(thisStep->transistion){
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
  return colorMixed;
}

//  byte percent;
//  int programNumber = 0;
//  int programStep = programStates[programNumber].currentStep;
//
//  byte nextStepNumber=nextStep(programNumber,programStep);
//  struct programStep thisStep = programs[programNumber].steps[programStep];
//  struct programStep nextStep = programs[programNumber].steps[nextStepNumber];
//  
//// Just execute program 1
//  unsigned long interval = millis()-programStates[programNumber].stepStartMilliseconds;
//  unsigned int duration = thisStep.durationInMilliseconds;
//  if(programStates[programNumber].keep==true){
//    percent = 0;
//    if(interval>thisStep.keepInMilliseconds){
//      programStates[programNumber].stepStartMilliseconds=millis();
//      programStates[programNumber].keep=false;
//    }
//  }else{
//    percent = (long)interval*100L/duration;
//    if(interval>duration){
//      programStates[programNumber].stepStartMilliseconds=millis();
//      programStates[programNumber].currentStep = nextStepNumber;
//      programStates[programNumber].keep=true;
//    }
//  }
//
////  byte lampNumber=0;
////  setDmxColor(lampNumber,colorMixed);
//  // Todo: How is the lamp shema stored within the program?
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
//}


struct stepState findStepState(unsigned long milliseconds,unsigned long offset,byte programNumber){
  // Calculate where we are... 
  // milliseconds is the golbal clock
  // offset is the offset relative to the global start time
  // Calculates the percentage in the current step and the keep/fade flag

  unsigned long timeWithinProgram = (milliseconds - globalProgramStart) %  programStates[programNumber].programDuration;

  stepState currentStepState;
  unsigned long programDuration=0;
  for(int i=0;i<programs[programNumber].numberOfSteps;i++){
    currentStepState.stepNumber=i;
    currentStepState.percent = (timeWithinProgram-programDuration)/(programs[programNumber].steps[i].keepInMilliseconds+1);//Avoid div/0
    programDuration+=programs[programNumber].steps[i].keepInMilliseconds;
    if(timeWithinProgram < programDuration){
      currentStepState.keep=true;
      return currentStepState;
    }
    currentStepState.percent = (timeWithinProgram-programDuration)/(programs[programNumber].steps[i].durationInMilliseconds+1);//Avoid div/0
    currentStepState.percent = timeWithinProgram-programDuration;
    programDuration+=programs[programNumber].steps[i].durationInMilliseconds;    
    if(timeWithinProgram < programDuration){
      currentStepState.keep=false;
      return currentStepState;
    }
  }
};

void programExecutor(){
  // Todo: Spagetthi coding
  if(programRunning==false){
    return;
  }
  if(reduceCalls()==true){
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

  RgbColor colorMixed = mixColorsOfSteps(&thisStep,&nextStep,percent);


  // Todo: How is the lamp shema stored within the program?
  LampSchema lampSchema = getLampSchema(0);
  for(byte i = 0;i<MAX_LAMPS;i++){
    byte lampNumber=lampSchema.sequence[i];
    if(lampNumber>0){
      LampData lampData = getLampData(lampNumber);
      if(lampData.active==true){
        setDmxColor(lampNumber,colorMixed);
      }
    }
  }
}

