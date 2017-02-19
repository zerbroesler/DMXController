// DMX Controller using a LCD Display for control
// 3 rotary encoders are used to control the values, push down for slow changes
// 1 rotary encoder is used to navigate through the menus, push down to select
// 
// Version for Arduino mega


#define NumKnobs 4
#define dmxChannel 4

#include <DmxSimple.h>
// Project includes
#include "DataModel.h"
#include "Display.h"
#include "Menu.h"
#include "InputControl.h"

#define dmxPin 22


float positions[NumKnobs];
int menuentry = 0;

void setup() {
  DmxSimple.usePin(dmxPin);
  DmxSimple.maxChannel(4);
  DmxSimple.write(dmxChannel,255);
  displaySetup();
  inputSetup();
  setMenuNumber(0);
  setMenuEntry(0);
}

void loop() {
  readKnobs();
  readMenuKnob();
  updateMenuEntry();
  drawMenu();
  drawMenuEntry();
  updateDisplay();
}




