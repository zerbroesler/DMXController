//
// Light scenes
//
// A light scene is a combination of programs.
// It is not checked if they conflict at the moment. 
// All programs are executed at the same time
//
// Be careful to not add two programs which influenece the same lamp
//
byte sceneNumber = 0;

struct Scene{
  byte programId[MAX_PROGRAMS * 2];
  
};
/*
  {0,2,0,4,0,6,0,0},  // 0 even
  {0,0,3,0,5,0,0,0},  // 1 odd
  {1,0,0,0,0,0,0,0},  // 2 Big one
  {0,0,0,0,0,0,0,8},  // 3 Superhell
  {0,2,3,4,5,6,0,0},  // 4 All small
  {1,2,3,4,5,6,0,8}   // 5 All together
*/  
struct Scene scenes[MAX_SCENES]={
  //Programs to run with 255 as end marker
  {0,0,
   1,1,
   2,2,
   2,3,
   255},
   // 2
  {3,1,
   4,0,
   2,2,
   2,3,
   255},
   // 3
  {7,5, 
   255},
   // 4
  {8,5,
   255},
   // Blackout button (Pause)
  {5,5,   
   255},
};

void setScene(byte newSceneNumber){
  sceneNumber = newSceneNumber;
  #ifdef debug
//    Serial.print(" Scene: " );
//    Serial.println( sceneNumber );
  #endif
}

byte getScene(byte){
  return sceneNumber;
}

void sceneRunner(){
  if(programRunning==false){
    return;
  }
  if(reduceCalls()==false){
    return;
  }
  
  byte programNumber;
  for(int i=0;i<MAX_PROGRAMS;i++){
    programNumber = scenes[sceneNumber].programId[i*2];
    if(programNumber==255){
      break;
    }
    byte lampSchemaNumber = scenes[sceneNumber].programId[i*2 + 1];
    unsigned long currentMillis = millis();
    Serial.print(currentMillis);
    Serial.print(programNumber);
    Serial.print(lampSchemaNumber);
    Serial.println("");
    executeProgram(currentMillis,programNumber,lampSchemaNumber/*,phaseDelay*/);
  }
}
