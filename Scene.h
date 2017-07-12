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

// Using Linked lists to reduce? memory footprint
//
LinkedList<LinkedList<struct Scene>*> sceneList = LinkedList<LinkedList<struct Scene>*>();
LinkedList<struct Scene> *currentScene;

void initScenes(){

  LinkedList<struct Scene> *scene= new LinkedList<struct Scene>;

  scene->add({5,4});
  sceneList.add(scene);

  scene= new LinkedList<struct Scene>();
  scene->add({6,0});
  scene->add({6,1});
  sceneList.add(scene);

  scene=new LinkedList<struct Scene>();
  scene->add({8,3});
  sceneList.add(scene);

  scene=new LinkedList<struct Scene>();
  scene->add({0,0});
  scene->add({1,1});
  scene->add({2,2});
  sceneList.add(scene);
  
  scene=new LinkedList<struct Scene>();
  scene->add({3,3});
  scene->add({4,2});
  sceneList.add(scene);
  
  scene=new LinkedList<struct Scene>();
  scene->add({7,4});
  sceneList.add(scene);

  #ifdef debug
    Serial.println("scene init done");
  #endif  
  currentScene = sceneList.get(0);
}

void setScene(byte newSceneNumber){
  sceneNumber = newSceneNumber;
  currentScene = sceneList.get(sceneNumber);
  
  #ifdef debug
//    Serial.println("-scenesize: ");
//    Serial.println(currentScene->size());
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
//  Serial.println("scene Runner running");
  byte programNumber;
  for(int i=0;i<currentScene->size();i++){
    programNumber =currentScene->get(i).programId;
//    Serial.println(programNumber);
    byte lampSchemaNumber = currentScene->get(i).lampSchema;
//    Serial.println(lampSchemaNumber);
    unsigned long currentMillis = millis();
    executeProgram(currentMillis,programNumber,lampSchemaNumber);
  }
}

