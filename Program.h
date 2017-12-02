//
// Light programs
//

#define RGB 1
#define HSV 2

#define FADE_RGB 1
#define FADE_HSV 2
#define FADE_RGB_LOW 3
#define FADE_RGB_GLOW 4
//#define FADE_CONSTANT 3

boolean programRunning = true;
long programSpeedStep=0;
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
};

struct programState programStates[MAX_PROGRAMS]={
  {0},
  {0},
};
// Auftritt Gartenkonzert Juli 2017
struct program programs[MAX_PROGRAMS]={
    { // 0 : Yellow, green
      2,          // Steps
      170,255,0,  //values
      RGB,        // RGB
      7000,       // keep duration before transistion
      1000,       // duration
      FADE_RGB,   // fade
      0,          // phase delay (unused)
    
      0,255,0,
      RGB,
      7000,   
      1000,
      FADE_RGB,
      0,
    },{ // 1 : Yellow, green inverse
      2,        // Steps
      0,255,0,  //values
      RGB,     // RGB
      7000,     // keep duration before transistion
      1000,     // duration
      FADE_RGB,  // fade
      0,        // phase delay
    
      170,255,0,
      RGB,
      7000,   
      1000,
      FADE_RGB,
      0,
      
    },{ // 2 : yellowgreen - cyanBlu
      2,        // Steps
      80,255,0, 
      RGB,     
      5000,     
      5000,     
      FADE_RGB, 
      0,        
    
      0,255,80,
      RGB,
      5000,   
      5000,
      FADE_RGB,
      0,
      
    },{ // 3 : Orange Yellow
      2,        // Steps
      255,200,50, 
      RGB,     
      3000,     
      3000,     
      FADE_RGB, 
      0,        
    
      255,150,20,
      RGB,
      3000,   
      3000,
      FADE_RGB,
      0,
    },{  // 4: Cyan
      3,        // Steps
      30,200,255, 
      RGB,     
      2000,     
      2000,     
      FADE_RGB, 
      0,        
    
      0,255,255,
      RGB,
      2000,   
      2000,
      FADE_RGB,
      0,

      0,255,155,
      RGB,
      2000,   
      2000,
      FADE_RGB,
      0,

    },{  // 5: Dark Blue
      2,        // Steps
      0,0,100, 
      RGB,     
      5000,     
      5000,     
      FADE_RGB, 
      0,        

      0,0,70,
      RGB,
      5000,   
      5000,
      FADE_RGB,
      0,
    },{  // 6: Deep Blue
      4,        // Steps
      0,0,255, 
      RGB,     
      4000,     
      2500,     
      FADE_RGB, 
      0,        
    
      0,50,50,
      RGB,
      0,   
      3500,
      FADE_RGB,
      0,

      0,255,0,
      RGB,
      4000,   
      2500,
      FADE_RGB,
      0,

      0,50,50,
      RGB,
      0,   
      3500,
      FADE_RGB,
      0,

    },{  // 7: Pink and Purple
      4,        // Steps
      255,40,40, 
      RGB,     
      4000,     
      2500,     
      FADE_HSV, 
      0,        
    
      220,0,255,
      RGB,
      4000,   
      2500,
      FADE_HSV,
      0,

      200,60,100,
      RGB,
      2000,   
      1500,
      FADE_HSV,
      0,

      255,50,0,
      RGB,
      1000,   
      2500,
      FADE_HSV,
      0,

    },{  // 8: White shades to yellow
      3,        // Steps
      255,255,255, 
      RGB,     
      5000,     
      2500,     
      FADE_HSV, 
      0,        
    
      255,255,150,
      RGB,
      5000,   
      2500,
      FADE_HSV,
      0,

      200,255,255,
      RGB,
      5000,   
      2500,
      FADE_HSV,
      0,
      
    },{  // 9: 
      3,        // Red
      255,50,50, 
      RGB,     
      5000,     
      2500,     
      FADE_HSV, 
      0,        
    
      255,0,0,
      RGB,
      5000,   
      2500,
      FADE_HSV,
      0,

      255,50,0,
      RGB,
      5000,   
      2500,
      FADE_HSV,
      0,
    },{  // 10: 
      3,        // Blue
      0,0,255, 
      RGB,     
      5000,     
      2500,     
      FADE_HSV, 
      0,        
    
      50,50,255,
      RGB,
      5000,   
      2500,
      FADE_HSV,
      0,

      50,0,255,
      RGB,
      5000,   
      2500,
      FADE_HSV,
      0,
    },{  // 11: 
      3,        // Violett
      100,0,255,
      RGB,     
      5000,     
      2500,     
      FADE_HSV, 
      0,        
    
      100,50,255,
      RGB,
      5000,   
      2500,
      FADE_HSV,
      0,

      50,0,200,
      RGB,
      5000,   
      2500,
      FADE_HSV,
      0,
    },{ // 12 : Blue-Yellow
      4,        // Steps
      50,50,255, 
      RGB,     
      5000,     
      5000,     
      FADE_RGB, 
      0,        
    
      50,100,150, 
      RGB,     
      5000,     
      3000,     
      FADE_RGB, 
      0,        

      255,255,50,
      RGB,
      5000,   
      5000,
      FADE_RGB,
      0,

      50,100,150,
      RGB,
      5000,   
      3000,
      FADE_RGB,
      0,
    },{ // 13 : Just White
      1,        // Steps
      255,255,255, 
      RGB,     
      5000,     
      5000,     
      FADE_RGB, 
      0,        
    },{ // 14 : Just Red
      1,        // Steps
      255,0,0, 
      RGB,     
      5000,     
      5000,     
      FADE_RGB, 
      0,        

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
  if(programSpeedStep < PROGRAMSPEED){
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
    case FADE_RGB_LOW:
      colorMixed = mixColorRGBLow(colorFrom,colorTo,percent);
      break;
    case FADE_RGB_GLOW:
      colorMixed = mixColorRGBGlow(colorFrom,colorTo,percent);
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
    currentStepState.percent = 0;
    programDuration+=programs[programNumber].steps[i].keepInMilliseconds;
    if(timeWithinProgram < programDuration){
      currentStepState.keep=true;
      return currentStepState;
    }
    currentStepState.percent = (byte)((timeWithinProgram-programDuration)*100/(programs[programNumber].steps[i].durationInMilliseconds+1));//Avoid div/0
    programDuration+=programs[programNumber].steps[i].durationInMilliseconds;    
    if(timeWithinProgram < programDuration){
      currentStepState.keep=false;
      return currentStepState;
    }
  }
};

RgbColor getColorForTimeAndProgram(unsigned long milliseconds,byte programNumber){

  byte percent;
  
  struct stepState currentStepState = findStepState(milliseconds,0,programNumber);
  int programStep=currentStepState.stepNumber;
  int nextStepNumber=nextStep(programNumber,programStep);
  struct programStep thisStep = programs[programNumber].steps[programStep];
  struct programStep nextStep = programs[programNumber].steps[nextStepNumber];
  return mixColorsOfSteps(&thisStep,&nextStep,currentStepState.percent);
}

void executeProgram(unsigned long currentMilliseconds,byte programNumber,byte lampSchemaNumber){
  if(programs[programNumber].numberOfSteps==0){
    return;
  }
//  byte lampSchemaNumber = programs[programNumber].lampSchema;
  RgbColor colorMixed = getColorForTimeAndProgram(currentMilliseconds,programNumber);

  LampSchema lampSchema = getLampSchema(lampSchemaNumber);

  for(byte i = 0;i<MAX_LAMPS;i++){
    byte lampNumber=lampSchema.sequence[i];
    if(lampNumber>0){
      LampData lampData = getLampData(lampNumber);
      if(lampData.active==true){
        setDmxColor(lampNumber,colorMixed);
        // Get color for next lamp
        colorMixed = getColorForTimeAndProgram(currentMilliseconds+(i+1)*800,programNumber);
      }
    }
  }
}

//void programExecutor(byte programNumber){
//
//  if(programRunning==false){
//    return;
//  }
//  if(reduceCalls()==true){
//    return;
//  }
//  unsigned long currentMillis = millis();
//
//  for(byte programNumber=0;programNumber<MAX_PROGRAMS;programNumber++){
//    executeProgram(currentMillis,programNumber);
//  }
//}

