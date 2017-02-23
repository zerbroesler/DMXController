int dmxAddress;
void nextDmxAddress(){
  dmxAddress++;
  dmxAddress%=128;
}
void previousDmxAddress(){
  dmxAddress--;
  dmxAddress=(dmxAddress+128)%128;
}
void menuSpecialDmxAddress(){
  long menuRelative = getMenuRelative();
  if(menuRelative>=4){
    setMenuRelative(-4);
    nextDmxAddress();
  }
  if(menuRelative <=-4){
    setMenuRelative(4);
    previousDmxAddress();
  }
  showValue(dmxAddress,7,1);

  if(getMenuPressed()==true){
    // Specific exit (mainly optical)
    switch(getMenuSpecial()){
      case 1:
        clearBrackets(6,1,3);
        showBrackets(0,1,5);
        break;
      default:
        break;
    }
    setMenuSpecial(0);
  }
}
