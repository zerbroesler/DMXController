// DMX Controller using a LCD Display for control
// 3 rotary encoders are used to control the values, push down for slow changes
// 1 rotary encoder is used to navigate through the menus, push down to select
// 
// Version for Arduino mega

#define debug


// Project includes
#include "Config.h"
#include "DataModel.h"
#include "DmxOut.h"
#include "Display.h"
#include "MenuEntries.h"
#include "Menu.h"
#include "MenuDMXTester.h"
#include "InputControl.h"



void setup() {
  #ifdef debug
  Serial.begin(57600);
  Serial.println("Debug started:");
  #endif

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
