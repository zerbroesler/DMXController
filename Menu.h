//
// Menu handling 
//
// A Menu consists of a Text (4x20 Characters)
// An array of x and y values where the menu items are
//

struct menuItem{
  byte x;
  byte y;
};
struct menuText{
  char text[3][21];
};
struct menuProperty{
  struct menuText menuText;
  byte menuLength;
  struct menuItem menuItems[10];
};
int menuNumber = 0;
int menuEntry = 0;
int oldMenuNumber = -1;
int oldMenuEntry = 1;
bool menuChanged = false;

menuProperty menuProperties[] = {
  "12345678901234567890",
   "Menu Line2",
   "          ",
  2, {{ 1,2 },{1,1}},
  "Second Menu",
  "Menu Line2",
  "          ",
  3, {{ 3,1 },{5,1},{8,1}}
};

void setMenuNumber(int number){
  menuNumber = number;
}

void setMenuEntry(int number){
  menuEntry = number;
}
void nextMenuEntry(){
  menuEntry++;
  if(menuEntry>=menuProperties[menuNumber].menuLength){
    menuEntry=0;
  }
}
void previousMenuEntry(){
  menuEntry--;
  if(menuEntry<0){
    menuEntry=(menuProperties[menuNumber].menuLength)-1;
  }
}

void updateMenuEntry(){
  long menuRelative = getMenuRelative();
  if(menuRelative>=4){
    setMenuValue(-4,false);
    nextMenuEntry();
  }
  if(menuRelative <=-4){
    setMenuValue(4,false);
    previousMenuEntry();
  }
}

void drawMenu(){
  if(oldMenuNumber==menuNumber){
    return;
  }
  lcdSetCursor(0,0);
  lcd.print(menuProperties[menuNumber].menuText.text[0]);
  lcd.setCursor(0,1);
  lcd.print(menuProperties[menuNumber].menuText.text[1]);
  lcd.setCursor(0,2);
  lcd.print(menuProperties[menuNumber].menuText.text[2]);
  oldMenuNumber=menuNumber;
}

void drawMenuEntry(){
  if(oldMenuEntry == menuEntry){
    return;
  }
  menuItem newMenuItem = menuProperties[menuNumber].menuItems[menuEntry];
  menuItem oldMenuItem = menuProperties[menuNumber].menuItems[oldMenuEntry];
  lcd.setCursor(oldMenuItem.x,oldMenuItem.y);
  lcd.print(" ");
  lcd.setCursor(newMenuItem.x,newMenuItem.y);
  lcd.print("*");
  oldMenuEntry = menuEntry;
}

