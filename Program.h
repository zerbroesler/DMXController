//
// Light programs
//

// a program could be moving / color
// or combined. lights with more than one possible color are not supported at the moment.
//


#define MAX_PROGRAMS 10
#define MAX_PROGRAM_STEPS 10

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
  int durationInMilliseconds;
  byte lampSchema;
  enum transistion transistion;
  boolean phaseTroughLamps; // starts the program for each lamp in lampSchema delayed by 1/lamps
};

struct program{
  int id;
  struct programStep steps[MAX_PROGRAM_STEPS];
};


struct program programs[MAX_PROGRAMS]={
  {
    1,
    {
      255,0,0,  //values
      true,     // RGB
      2000,     // duration
      1,        // lamp schema
      fadeRGB,  // fade
      false     // phase through
      }
    },
  {
    2,
    }
};

unsigned long oldTime;

int getIntervalMS(){
  
};
bool checkProgramRunning(int number){
  
};


void startProgram(int number){
  checkProgramRunning(number);

  // Error: Conflict with running program
  
};
void stopProgram(int number){
  
};
void stopAllPrograms(){
  
};

void programExecutor(){

int interval = getIntervalMS();

//  getRunningPrograms();

//  for(){
//    getValuesFromProgram()
//  }
}

