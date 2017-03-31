//
// Light scenes
//
// A light scene is a combination of programs.
// It is not chekced if thex conflict at the moment. 
// Be careful to not add two programs which influenece the same lamp
//
byte sceneNumber = 0;

struct Scene{
  byte programId;
  byte lampSchema;
};

LinkedList<LinkedList<struct Scene>> sceneList = LinkedList<LinkedList<struct Scene>>();
LinkedList<struct Scene> currentScene;

void initScenes(){

  LinkedList<struct Scene> scene=LinkedList<struct Scene>();

  scene.add({5,4});
  sceneList.add(scene);
  scene=LinkedList<struct Scene>();
  scene.add({6,0});
  scene.add({6,1});
  sceneList.add(scene);

  scene=LinkedList<struct Scene>();
  scene.add({8,3});
  sceneList.add(scene);
  scene=LinkedList<struct Scene>();
  scene.add({0,0});
  scene.add({1,1});
  scene.add({2,2});
  sceneList.add(scene);
  scene=LinkedList<struct Scene>();
  scene.add({3,3});
  scene.add({4,2});
  sceneList.add(scene);
  scene=LinkedList<struct Scene>();
  scene.add({7,4});
  sceneList.add(scene);

  
  /*
      Serial.println("scene init A");
  LinkedList<struct Scene> scene3=LinkedList<struct Scene>();
  scene3.add({0,0});
  sceneList.add(scene3);
      Serial.println("scene init B");
  sceneList.add(scene2);
      Serial.println("scene init C");
*/
  #ifdef debug
    Serial.println("scene init done");
  #endif  
  currentScene = sceneList.get(0);
};

/*
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
  {0,0,
   1,1,
   255},
  {3,3,
   4,2,
   255}, //5
  {7,4,
   255}, 
};
*/

void setScene(byte newSceneNumber){
  sceneNumber = newSceneNumber;
  currentScene = sceneList.get(sceneNumber);
  /*
  #ifdef debug
    Serial.println("-scenesize: ");
    Serial.println(currentScene.size());
  #endif
  */
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
  for(int i=0;i<currentScene.size();i++){
    programNumber =currentScene.get(i).programId;
    Serial.println(programNumber);
    byte lampSchemaNumber = currentScene.get(i).lampSchema;
    Serial.println(lampSchemaNumber);
    unsigned long currentMillis = millis();
    executeProgram(currentMillis,programNumber,lampSchemaNumber);
  }
}

