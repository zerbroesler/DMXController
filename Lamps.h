//
// Lamp functions and definition
//


struct LampData{
	bool active;     // On or off
	int  dmxAddress; //
	int  dmxType;
};
struct LampData lampsData[] = {
  // Temporary until ui config exists
	{true,1,0},
	{true,11,0},
	{false,21,0},
};
int lampCount = sizeof(lampsData)/sizeof(lampsData[0]);


void setLampCount(int count){
  lampCount = count;
}
int getLampCount(){
  return lampCount;
}

struct LampData getLampData(int lampNumber){
  return lampsData[lampNumber];
};
