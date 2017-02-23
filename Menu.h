//
// Menu handling 
//
// A Menu consists of a Text (20x4 Characters)
// An array of x and y values where the menu items are
//

void handleMenuSpecial();
void menuSpecialDmxAddress();
void menuSpecialDmxChannel();

int menuSpecial = 0;
int menuNumber = 0;
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
void showBrackets(int x,int y,int width){
  lcd.setCursor(x,y);
  lcd.print("(");
  lcd.setCursor(x+width+1,y);
  lcd.print(")");
}
void clearBrackets(int x,int y,int width){
  lcd.setCursor(x,y);
  lcd.print(" ");
  lcd.setCursor(x+width+1,y);
  lcd.print(" ");
}

void setMenuSpecial(int number){
  menuSpecial = number;
  // Specific setup (mainly optical)
  switch(menuSpecial){
    case 1:
      clearBrackets(0,1,5);
      showBrackets(6,1,3);
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
//      menuSpecialDmxChannel();
      break;
    default:
    // Just ignore?
    #ifdef debug
      Serial.print("Illegal entry in menuspecial found:");
      Serial.print(getMenuSpecial());
    #endif
  }
}

void updateMenu(){
  if(getMenuSpecial()!=0){
    handleMenuSpecial();
  }
  long menuRelative = getMenuRelative();
  if(menuRelative>=4){
    setMenuRelative(-4);
    nextMenuEntry();
  }
  if(menuRelative <=-4){
    setMenuRelative(4);
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
  oldMenuNumber=menuNumber;
}


void drawMenuEntry(){
  if(oldMenuEntry == menuEntry){
    return;
  }
  menuProperty menu = getMenuProperty();
  menuItem newMenuItem = menu.menuItems[menuEntry];
  menuItem oldMenuItem = menu.menuItems[oldMenuEntry];
  clearBrackets(oldMenuItem.x,oldMenuItem.y,oldMenuItem.width);
  showBrackets(newMenuItem.x,newMenuItem.y,newMenuItem.width);

  oldMenuEntry = menuEntry;
}

