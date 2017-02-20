// DMX Controller using a LCD Display for control
// 3 rotary encoders are used to control the values, push down for slow changes
// 1 rotary encoder is used to navigate through the menus, push down to select
// 
// Version for Arduino mega


#define NumKnobs 4

// Project includes
#include "DataModel.h"
#include "DmxOut.h"
#include "Display.h"
#include "Menu.h"
#include "InputControl.h"



float positions[NumKnobs];
int menuentry = 0;

void setup() {
  dmxSetup();
  displaySetup();
  inputSetup();
  setMenuNumber(0);
  setMenuEntry(0);
}

void loop() {
  readKnobs();
  readMenuKnob();
  updateMenu();
  drawMenu();
  drawMenuEntry();
  updateDisplay();
//  dmxWrite();
}




