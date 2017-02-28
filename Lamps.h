//
// Lamp functions and definition
//
#define MAX_LAMP_SCHEMAS 5
#define MAX_LAMPS 10

struct LampData{
	bool active;     // On or off
	int  dmxAddress; //
	int  dmxType;
};
struct LampData lampsData[MAX_LAMPS] = {
  // Temporary until ui config exists
	{true,1,0},
	{true,11,0},
	{false,21,0},
};

// Shema is a list of lamps used in a program.
// It holds the lamp numbers and the sequence they are used.
// 0=Not used, other = sequence number
struct LampSchema{
  int sequence[MAX_LAMPS];
};

struct LampSchema lampSchemas[MAX_LAMP_SCHEMAS] = {
  {1,2,0,0,0,0,0,0,0,0},
  {4,3,2,1,0,0,0,0,0,0},
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

