//
// Menu handling 
//
// A Menu consists of a Text (4x20 Characters)
// An array of x and y values where the menu items are
//

struct menu{
  byte x;
  byte y;
};
int menuNumber = 0;
int menuEntry = 0;
int oldMenuNumber = -1;
int oldMenuEntry = -1;
bool menuChanged = false;

char menuTexts[][3][21] = {{"12345678901234567890",
                        "Menu Line2",
                        "          "},
                        {"Second Menu",
                        "SM Line2",
                        ""          }};

menu menuItems[][10] = {
  {{ 1,2 }, {1,1}},
  {{ 3,1 }, {1,1}}};

void setMenu(int number){
  menuNumber = number;
}

void setMenuEntry(int number){
  menuEntry = number;
}
void nextMenuEntry(){
  menuEntry++;
  if(menuEntry>1){
    menuEntry=0;
  }
}
void previousMenuEntry(){
  menuEntry--;
  if(menuEntry<0){
    menuEntry=1;
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
  lcd.print(menuTexts[menuNumber][0]);
  lcd.setCursor(0,1);
  lcd.print(menuTexts[menuNumber][1]);
  lcd.setCursor(0,2);
  lcd.print(menuTexts[menuNumber][2]);
  oldMenuNumber=menuNumber;
}

void drawMenuEntry(){
  if(oldMenuEntry == menuEntry){
    return;
  }
  menu menuItem = menuItems[menuNumber][menuEntry];
  menu oldMenuItem = menuItems[menuNumber][oldMenuEntry];
  lcd.setCursor(oldMenuItem.x,oldMenuItem.y);
  lcd.print(" ");
  lcd.setCursor(menuItem.x,menuItem.y);
  lcd.print("*");
  oldMenuItem = menuItem;
}

