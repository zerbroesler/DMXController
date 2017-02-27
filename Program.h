//
// Light programs
//

// a program could be moving / color
// or combined. lights with more than one possible color are not supported at the moment.
//


#define MAX_PROGRAMS 10
#define MAX_PROGRAM_STEPS 10

boolean programRunning = true;

enum transistion{
  fadeRGB,
  fadeHSV,
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
  unsigned int durationInMilliseconds;
  byte lampSchema;
  enum transistion transistion;
  boolean phaseTroughLamps; // starts the program for each lamp in lampSchema delayed by 1/lamps
};

struct program{
//  int id;
  struct programStep steps[MAX_PROGRAM_STEPS];
};

struct programState{
  unsigned long stepStartMilliseconds;
  int currentStep;
};

struct programState programStates[MAX_PROGRAMS]={
  {0,0},
  {0,0}
};

struct program programs[MAX_PROGRAMS]={  // Demo program fade between Red and Blue 2&1 Second
    {
      255,0,0,  //values
      true,     // RGB
      5000,     // duration
      1,        // lamp schema
      fadeRGB,  // fade
      false,     // phase through
    
      0,100,255,  //values
      true,     // RGB
      1000,     // duration
      1,        // lamp schema
      fadeRGB,  // fade
      false     // phase through
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
  programStates[number].currentStep=0;
  // Error: Conflict with running program
  programRunning=true;
  
};
void stopProgram(){
  programRunning=false;
};
void stopAllPrograms(){
  
};

byte mixColor(int color1, int color2,int percent){
  int mixed = ((color1*(100-percent))+(color2*percent))/200;
  return (byte)mixed;
};

void programExecutor(){
  if(programRunning==false){
    return;
  }
  int programNumber = 0;
  int programStep = 0;

  struct programStep thisStep = programs[programNumber].steps[programStep];
  struct programStep nextStep = programs[programNumber].steps[programStep+1];
  
// Just execute program 1
  unsigned long interval = millis()-programStates[programNumber].stepStartMilliseconds;
  unsigned int duration = thisStep.durationInMilliseconds;
  if(interval>duration){
    programStates[programNumber].stepStartMilliseconds=millis();
  }

  // Calculate the color
  int r1 = thisStep.values.r;
  int g1 = thisStep.values.g;
  int b1 = thisStep.values.b;
  
  int r2 = nextStep.values.r;
  int g2 = nextStep.values.g;
  int b2 = nextStep.values.b;

  byte percent = (long)interval*100L/duration;
  byte r = mixColor(r1,r2,percent);
  byte g = mixColor(g1,g2,percent);
  byte b = mixColor(b1,b2,percent);

  setDmxColor(0,r);
  setDmxColor(1,g);
  setDmxColor(2,b);

//  getRunningPrograms();

//  for(){
//    getValuesFromProgram()
//  }
}

