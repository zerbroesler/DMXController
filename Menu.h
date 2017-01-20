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


char menuTexts[][21] = {"12345678901234567890",
                        "Menu Line2"          ,
                        "          "          };

menu menuItems[][10] = {
  {{ 1,2 }, {1,1}},
  {{ 3,1 }, {1,1}}};

void drawMenu(int number){
  lcd.setCursor(0,0);
  lcd.print(menuTexts[number*3]);
  lcd.setCursor(0,1);
  lcd.print(menuTexts[number*3+1]);
  lcd.setCursor(0,2);
  lcd.print(menuTexts[number*3+1]);
}

void updateMenu(int number, int item){
  menu menuItem = menuItems[number][item];
  lcd.setCursor(menuItem.x,menuItem.y);
  lcd.print("*");
}

