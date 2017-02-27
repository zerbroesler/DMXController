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
    {
      255,0,255,  //values
      true,     // RGB
      2000,     // duration
      1,        // lamp schema
      fadeRGB,  // fade
      false     // phase through
      }
  },{
    {
      0,0,255,  //values
      true,     // RGB
      1000,     // duration
      1,        // lamp schema
      fadeRGB,  // fade
      false     // phase through
    }
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

void programExecutor(){
  if(programRunning==false){
    return;
  }
  int programNumber = 0;
  int programStep = 0;
// Just execute program 1
  unsigned long interval = millis()-programStates[programNumber].stepStartMilliseconds;
  unsigned int duration = programs[programNumber].steps[programStep].durationInMilliseconds;
  if(interval>duration){
    programStates[programNumber].stepStartMilliseconds=millis();
  }

  // Calculate the color
  byte r = programs[programNumber].steps[programStep].values.r;
  byte g = programs[programNumber].steps[programStep].values.g;
  byte b = programs[programNumber].steps[programStep].values.b;

  setDmxColor(0,r);
  setDmxColor(1,g);
  setDmxColor(2,b);

//  getRunningPrograms();

//  for(){
//    getValuesFromProgram()
//  }
}

