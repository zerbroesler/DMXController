//
// Light scenes
//
// A light scene is a combination of programs.
<<<<<<< HEAD
// It is not checked if they conflict at the moment. 
=======
// It is not chekced if they conflict at the moment. 
// All programs are executed at the same time
//
>>>>>>> parent of 3bf98e4... Revert "Comment change"
// Be careful to not add two programs which influenece the same lamp
//
byte sceneNumber = 0;

struct Scene{
  byte programId[MAX_PROGRAMS * 2];
  
};


struct Scene scenes[MAX_SCENES]={
  //Programs to run with 255 as end marker
  {5,4,
   255},
  {6,0,
   6,1,
   255},
  {8,3,
   255},
  {0,0,
   1,1,
   2,2,
   255},
  {3,3,
   4,2,
   255},
  {3,3,
   4,2,
   255}, //5
  {7,4,
   255}, 
};

void setScene(byte newSceneNumber){
  sceneNumber = newSceneNumber;
  #ifdef debug
    Serial.print(" Scene: " );
    Serial.println( sceneNumber );
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
    executeProgram(currentMillis,programNumber,lampSchemaNumber);
    break;
  }
}
