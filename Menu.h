//
// Menu handling 
//
// A Menu consists of a Text (20x4 Characters)
// An array of x and y values where the menu items are
//

void handleMenuSpecial();
void menuSpecialDmxAddress();
void menuSpecialDmxChannel();
void menuSpecialDmxAddressInit();
void menuSpecialDmxChannelInit();
void menuDmxTesterInit();

int menuSpecial = 0;
int menuNumber = 0;
int menuId = 0;
int menuEntry = 0;
int oldMenuNumber = -1;
int oldMenuEntry = 1;
bool menuChanged = false;



struct menuProperty getMenuProperty(){
  return menuProperties[menuNumber];
}

void setMenuNumber(int number){
  menuNumber = number;
  menuSpecial = 0;  // Special have to end since the menu changed
  switch(menuId){
    case 4:    // Test menu
      setKnobsLinear();
      break;
    default:
      setKnobsLogarithmic();
      break;
  }
}

void setMenuEntry(int number){
  menuEntry = number;
  oldMenuEntry = 1;
}
void nextMenuEntry(){
  menuEntry++;
  if(menuEntry>=getMenuProperty().menuLength){
    menuEntry=0;
  }
}
void previousMenuEntry(){
  menuEntry--;
  if(menuEntry<0){
    menuEntry=getMenuProperty().menuLength-1;
  }
}

void showAround(int x,int y,int width,char start,char ending){
  lcd.setCursor(x,y);
  lcd.print(start);
  lcd.setCursor(x+width+1,y);
  lcd.print(ending);
}

void showAngleBrackets(int x,int y,int width){
  showAround(x,y,width,'<','>');
}
void showBrackets(int x,int y,int width){
  showAround(x,y,width,'(',')');
}
void clearAround(int x,int y,int width){
  showAround(x,y,width,' ',' ');
}

void setMenuSpecial(int number){
  menuSpecial = number;
  // Specific setup (mainly optical)
  switch(menuSpecial){
    case 1:
      menuSpecialDmxAddressInit();
      break;
    case 2:
      menuSpecialDmxChannelInit();
      break;
    default:
      break;
  }
}
int getMenuSpecial(){
  return menuSpecial;
}

void jumpToMenu(int to){
  byte index = 0;
  menuId=to;
  for(int i=0;i<MENUENTRIES;i++){
    if(menuProperties[i].id==to){
      index = i;
      break;
    }
  }
  setMenuNumber(index);
  setMenuEntry(0);
}

void jumpToSpecialControl(int number){
  // Display is kept, but the menu controller now controls
  // something different like a value on the screen
  setMenuSpecial(number);
}


void navigateMenu(){
  int to = getMenuProperty().menuItems[menuEntry].to;
  if(to > 0){
    jumpToMenu(to);
  }else if(to < 0){
    jumpToSpecialControl(-to);
  }
}
void handleMenuSpecial(){
  switch(getMenuSpecial()){
    case 1:
      menuSpecialDmxAddress();
      break;
    case 2:
      menuSpecialDmxChannel();
      break;
    default:
    // Just ignore?
    #ifdef debug
      Serial.print("Illegal entry in menuspecial found:");
      Serial.print(getMenuSpecial());
    #endif
  }
}

int getRelativeMenuStep(){
  int relative = 0;
  long menuRelative = getMenuRelative();
  if(menuRelative>=4){
    setMenuRelative(-4);
    relative=1;
  }
  if(menuRelative <=-4){
    setMenuRelative(4);
    relative=-1;
  }
  return relative;
}

void updateMenu(){
  if(getMenuSpecial()!=0){
    handleMenuSpecial();
  }
  int relativeStep = getRelativeMenuStep();
  if(relativeStep==1){
    nextMenuEntry();
  }else if(relativeStep==-1){
    previousMenuEntry();
  }
  if(getMenuPressed()==true){
    navigateMenu();
  }
}

void drawMenu(){
  if(oldMenuNumber==menuNumber){
    return;
  }
  menuProperty menu = getMenuProperty();
  lcdSetCursor(0,0);
  lcd.print(menu.menuText.text[0]);
  lcd.setCursor(0,1);
  lcd.print(menu.menuText.text[1]);
  lcd.setCursor(0,2);
  lcd.print(menu.menuText.text[2]);
  switch(menuId){
    case 4:    // Test menu
      menuDmxTesterInit();
      break;
    default:
      break;
  }

  oldMenuNumber=menuNumber;
}


void drawMenuEntry(){
  if(oldMenuEntry == menuEntry){
    return;
  }
  menuProperty menu = getMenuProperty();
  menuItem newMenuItem = menu.menuItems[menuEntry];
  menuItem oldMenuItem = menu.menuItems[oldMenuEntry];
  clearAround(oldMenuItem.x,oldMenuItem.y,oldMenuItem.width);
  showBrackets(newMenuItem.x,newMenuItem.y,newMenuItem.width);

  oldMenuEntry = menuEntry;
}

