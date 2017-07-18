//
// Lamp functions and definition
//
#define MAX_LAMP_SCHEMAS 5
#define MAX_LAMPS 8

struct LampData{
	bool active;     // On or off
	int  dmxAddress; //
	int  dmxType;
};
struct LampData lampsData[MAX_LAMPS] = {
  // Temporary until ui config exists
	{true,1,0},
	{true,11,1},
	{true,21,1},
  {true,31,1},
  {true,41,1},
  {true,51,1},
  {true,61,1},
  {true,101,2},
};

// Shema is a list of lamps used in a program.
// It holds the lamp numbers and the sequence they are used.
// 0=Not used, other = sequence number
struct LampSchema{
  int sequence[MAX_LAMPS];
};

struct LampSchema lampSchemas[MAX_LAMP_SCHEMAS] = {
  {1,0,3,0,5,0,0,0},
  {0,2,0,4,0,6,0,0},
  {0,0,0,0,0,0,0,8},  // 2 Superhell
  {1,2,3,4,5,6,0,0},  // 3 All small
  {1,2,3,4,5,6,0,8},  // 4 All together
};

int lampCount = sizeof(lampsData)/sizeof(lampsData[0]);


void setLampCount(int count){
  lampCount = count;
}
int getLampCount(){
  return lampCount;
}

struct LampData getLampData(int lampNumber){
  return lampsData[lampNumber-1];
};

struct LampSchema getLampSchema(int lampSchemaNumber){
  return lampSchemas[lampSchemaNumber];
};

