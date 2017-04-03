#define MENUENTRIES 4
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

menuProperty menuProperties[MENUENTRIES] = {
//"12345678901234567890",
// Entry screen
  "   DMX Controller   ",
  "  Run   Lamps  Prog ",
  " Scenes Test        ",
  1,   5, {
    //X,Y, to
    { 1,1,3,  2},  // Run
    { 7,1,5,  3},  // Lamps
    {14,1,4,  0},  // Prog
    { 0,2,6,  0},  // Scenes
    { 7,2,4,  4}}, // Test
//
//"12345678901234567890",
  " <   Run Scene      ",
  " 1 2 3 4 5 6 7 8 9  ",
  " Speed       Bright ",
  2, 10, {
    {0,0,1,  1}, // Back
    {0,1,1,  -81},
    {2,1,1,  -82},
    {4,1,1,  -83},
    {6,1,1,  -84},
    {8,1,1,  -85},
    {10,1,1,  -86},
    {12,1,1,  -87},
    {14,1,1,  -88},
    {16,1,1,  -89}},
//
//"12345678901234567890",
  " <   Lamp setup     ",
  " 1 2 3 4 5 6 7 8 9  ",
  "Addr:    Type:RGBW  ",  // DMX start adress + Lamp type
//  ???
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
  "                    ", // Shows dmx offset (relative to address)
                          // Shows values
  4, 3, {
    {0,0,2,  1}, // Back
    {0,1,5, -1}, // Address selection
    {10,1,8,-2}} // channel carousel
};

