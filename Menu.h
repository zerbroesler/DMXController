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
  int to;
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
int menuSpecial = 0;
int menuNumber = 0;
int menuEntry = 0;
int oldMenuNumber = -1;
int oldMenuEntry = 1;
bool menuChanged = false;

#define MENUENTRIES 4
menuProperty menuProperties[] = {
//"12345678901234567890",
// Entry screen
  "   DMX Controller   ",
  " Lamps  Color  Prog ",
  " Test               ",
  1,   4, {
    //X,Y, to
    { 0,1,5,  2},  // Lamps
    { 7,1,5,  3},  // Color
    {14,1,4,  0},  // Prog
    { 0,2,4,  4}}, // Test
//
//"12345678901234567890",
  " < Lamp selection   ",
  " 1 2 3 4 5 6 7 8 <- ",
  "          ",
  2, 10, {
    {0,0,1,  1}, // Back
    {0,1,1,  0},
    {2,1,1,  0},
    {4,1,1,  0},
    {6,1,1,  0},
    {8,1,1,  0},
    {10,1,1,  0},
    {12,1,1,  0},
    {14,1,1,  0},
    {16,1,2,  1}},
//
//"12345678901234567890",
  " <  Color chooser   ",
  " 1 2 3 4 5 6 7 8 <- ",
  "          ",
  3, 10, {
    {0,0,2,  1}, // Back
    {0,1,1,  0},
    {2,1,1,  0},
    {4,1,1,  0},
    {6,1,1,  0},
    {8,1,1,  0},
    {10,1,1,  0},
    {12,1,1,  0},
    {14,1,1,  0},
    {16,1,2,  1}},
//"12345678901234567890",
  " <   DMX Tester     ",
  " Addr:     Channels ",
  "<                  >",
  4, 3, {
    {0,0,2,  1}, // Back
    {0,1,5, -1}, // Address selection
    {10,1,8,-2}} // channel carousel
};

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

int dmxAddress;
void nextDmxAddress(){
  dmxAddress++;
  dmxAddress%=128;
}
void previousDmxAddress(){
  dmxAddress--;
  dmxAddress=(dmxAddress+128)%128;
}
void menuSpecialDmxAddress(){
  long menuRelative = getMenuRelative();
  if(menuRelative>=4){
    setMenuRelative(-4);
    nextDmxAddress();
  }
  if(menuRelative <=-4){
    setMenuRelative(4);
    previousDmxAddress();
  }
  showValue(dmxAddress,7,1);
  
  if(getMenuPressed()==true){
    // Specific exit (mainly optical)
    switch(getMenuSpecial()){
      case 1:
        clearBrackets(6,1,3);
        showBrackets(0,1,5);
        break;
      default:
        break;
    }
    setMenuSpecial(0);
  }
}


void jumpToSpecialControl(int number){
  // Display is kept, but the menu controller now controls
  // something different like a value on the screen
  setMenuSpecial(number);
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

void navigateMenu(){
  int to = getMenuProperty().menuItems[menuEntry].to;
  if(to > 0){
    jumpToMenu(to);
  }else if(to < 0){
    jumpToSpecialControl(-to);
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

