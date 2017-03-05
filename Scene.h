//
// Light scenes
//
// A light scene is a combination of programs.
// It is not chekced if thex conflict at the moment. 
// Be careful to not add two programs which influenece the same lamp
//
#define MAX_SCENES 10

struct Scene{
  byte programId[MAX_PROGRAMS];
  
};


struct Scene scenes[MAX_SCENES]={
  {0,255},
  {1,255},
  {2,255},
  {0,1,2,255},
  {0,1,255},
  {3,4,255}, //5
};

void sceneRunner(byte sceneNumber){
  byte programNumber;
  for(int i=0;i<MAX_PROGRAMS;i++){
    programNumber = scenes[sceneNumber].programId[i];
    if(programNumber==255){
      break;
    }
    unsigned long currentMillis = millis();
    executeProgram(currentMillis,programNumber);
  }
}

