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

void drawMenu(){
  lcd.setCursor(0,0);
  lcd.print(menuTexts[menuNumber][0]);
  lcd.setCursor(0,1);
  lcd.print(menuTexts[menuNumber][1]);
  lcd.setCursor(0,2);
  lcd.print(menuTexts[menuNumber][2]);
}

void updateMenu(){
  menu menuItem = menuItems[menuNumber][menuEntry];
  lcd.setCursor(menuItem.x,menuItem.y);
  lcd.print("*");
}

