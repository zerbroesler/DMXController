// DMX Controller using a LCD Display for control
// 3 rotary encoders are used to control the values, push down for slow changes
// 1 rotary encoder is used to navigate through the menus, push down to select
// 
// Version for Arduino mega



// Project includes
#include "Config.h"
#include "DataModel.h"
#include "DmxOut.h"
#include "Display.h"
#include "Menu.h"
#include "InputControl.h"



void setup() {
  //  Serial.begin(57600);
  //  Serial.println("Debug:");

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
  // DMX is automatically updated via timer interrupt of DMXSimple library
}
