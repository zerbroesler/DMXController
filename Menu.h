//
// Menu handling 
//
// A Menu consists of a Text (20x4 Characters)
// An array of x and y values where the menu items are
//

struct menuItem{
  byte x;
  byte y;
  byte width;
  byte to;
};
struct menuText{
  char text[3][21];
};
struct menuProperty{
  struct menuText menuText;
  byte id;
  byte menuLength;
  struct menuItem menuItems[10];
};
int menuNumber = 0;
int menuEntry = 0;
int oldMenuNumber = -1;
int oldMenuEntry = 1;
bool menuChanged = false;

#define MENUENTRIES 2
menuProperty menuProperties[] = {
//"12345678901234567890",
// Entry screen
  "   DMX Controller   ",
  " Lamps  Color  Prog ",
  "                    ",
  1,   3, {
    //X,Y, to
    { 0,1,5,  2},  // Lamps
    { 7,1,5,  2},  // Color
    {14,1,4,  0}}, // Prog
//
//"12345678901234567890",
  "   Lamp selection   ",
  " 1 2 3 4 5 6 7 8 9  ",
  "          ",
  2, 9, {
    {0,1,1,  0},
    {2,1,1,  0},
    {4,1,1,  0},
    {6,1,1,  0},
    {8,1,1,  0},
    {10,1,1,  0},
    {12,1,1,  0},
    {14,1,1,  0},
    {16,1,1,  0}}
};

struct menuProperty getMenuProperty(){
  return menuProperties[menuNumber];
}

void setMenuNumber(int number){
  menuNumber = number;
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

void navigateMenu(){
  byte to = getMenuProperty().menuItems[menuEntry].to;
  byte index = 0;
  if(to != 0){
    for(int i=0;i<MENUENTRIES;i++){
      if(menuProperties[i].id==to){
        index = i;
        break;
      }
    }
    setMenuNumber(index);
    setMenuEntry(0);
  }
}

void updateMenu(){
  long menuRelative = getMenuRelative();
  if(menuRelative>=4){
    setMenuValue(-4);
    nextMenuEntry();
  }
  if(menuRelative <=-4){
    setMenuValue(4);
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
  lcd.setCursor(oldMenuItem.x,oldMenuItem.y);
  lcd.print(" ");
  lcd.setCursor(oldMenuItem.x+oldMenuItem.width+1,oldMenuItem.y);
  lcd.print(" ");
  lcd.setCursor(newMenuItem.x,newMenuItem.y);
  lcd.print("(");
  lcd.setCursor(newMenuItem.x+newMenuItem.width+1,newMenuItem.y);
  lcd.print(")");
  oldMenuEntry = menuEntry;
}

