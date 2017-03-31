# DMXController
An Arduino Mega DMX Controller with LCD Display

This is the software / documentation part of the arduino dmx controller project.

## Hardware
* Arduino mega
* 4 rotary encoders
* 1 LCD display 20x4 characters with I2c connector
* RS485 encoder with XLR connector to connect DMX devices (Lamps)

More details on my Homepage
Schematics follow...

## Software
The software has a program executor and an UI which uses an 20x4 characters display and some rotary encoders / buttons.

## UI
The UI shows menus which lead to other menus. This is needed due to the lack of space on the display.
The 4th row of the display is usually used to show the values of the three rotary encoders. To make it obvious that the values belong to them they are physically placed directly below the display. They usually show RGB or HSV values, but could also show a speed value or other timing values


### Main Menu
The main menu leds to the other menus
* Run
* Program
* Lamps
* Test
* Sequences (of programs)
Screen:
```
   DMX Controller   
(Run *)   Program 
 Lamps    Test
   1         10
```

### Run scene
Scene = combination of programs.
Selects a scene to run. Only one scene can be active at the same time. Changing the scene will fade to the next scene within a short time (1/2 second).
Scenes can be selected via the additional hardware buttons attached to pins 45, 47, 49, 51, 53 of the arduino mega.
The speed can be adjusted with knob 1.
Master brigthness can be adjusted with knob 3
A scene can be selected by the menu knob. Selecting one scene will cancel the scene selected before. The selected scene is shown with an 'X' instead of the scene number.

Screen:
```
 <    Run Scene
(1)2 3 X 5 6 7 8 9
Speed         Bright
 100           100
```

A scene consists of a list of programs assigned to a lamp schema. 

 
### Program
Used to program a self-running show. It is possible to assign different programs to a scene.
Programs need to be combined to scenes.
A program consists of the following elements:

#### Name
A optional name to identify the program. Not yet implemented

#### Effect
A effect of this program which can be one of the following:
* Fade RGB
* Fade HSV

#### cycle
Cycle through the assigned light in the sequence they are defined (change sequence possible?=> in light setup)
* Time delay in ms   // Currently hard coded
* Over all lamps
* 1/x th of whole sequence

#### colors / timing
A list of colors which are used together with the timings in milliseconds. There are predefined colors, but they can also be selected via the rgb/hsv knobs

#### total speed
Total speed for one 100% cycle in seconds. Currently not available.

### Lamps groups
Assign lamps to lamp groups and edit their sequence. The same sequence number... (not possible, or meaningful?)
```
Group: 1
 1 2 3 4 5 6 7 8
 1   2   3
```

### DMX setup
Assign lamp numbers to DMX addresses, select the DMX type (RGB, RGBW, other)
For other there may be an assistant like "Test" which asks to identify the required channel like: "search for red channel".

### Test
Test the DMXdevices connected.
The start address can be selected via "Addr:". When "Channels" is selected, the channels relative to the start address can be scrolled through with the menu knob. The three knobs change the according channel shown in the ui. They have a step of 5 and a step of 1 when they are pressed.

```
 <   DMX Tester     
 Addr:  1  Channels                     
< 1       2      3 >
  0      35    220
```
