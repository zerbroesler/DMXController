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
It is mainly an ui which uses an 20x4 characters display and some rotaty encoders / buttons.

## UI
The UI shows menus which lead to other menus. This is needed due to the lack of space on the display.
The 4th row of the display is usually used to show the values of the three rotary encoders. To make it obvious that the values belong to them they are physically placed directly below the display. They usually show RGB or HSV values.


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

### Run
Just runs the program. It has no UI, so it runs even when the user does something different in the ui. The speed and the program number can be adjusted in the main menu with knobs 1 and 2. Knob 3 is currently not assigned.

### Program
Used to program a self-running show. Several programms can be defined, but currently only one is executed at a time. It may be possible to assign different programs to different lamps and run them simultaneously, but this is currently not possible.

A program consists of the following elements

#### Number
Number to store the program. To make it not too confusing and since memory is limited there are currently 5 Programs supported. They may be started / changed via physical buttons attached to pins 45, 47, 49, 51, 53 of the arduino mega.

#### Assigned Lamps
A Lamp configuration which use the program

#### Effect
A effect of this program which can be one of the following:
* Fade RGB
* Fade HSV
* Switch (Blink)
* Static (No change over time)
* Cycle through the assigned light in the sequence they are defined (change sequence possible?=> in light setup)

#### colors / timing
A list of colors which are used together with the timings in %. There are predefined colors, but they can also be selected via the rgb/hsv knobs

#### total speed
Total speed for one 100% cycle in seconds

### Lamps
Assign lamps to lamp groups and edit their sequence. The same sequence number... (not possible, or meaningful?)
```
Group: 1
 1 2 3 4 5 6 7 8
 1   2   3
```

### Test
Test the DMXdevices connected.
The start address can be selected via "Addr:". When "Channels" is selected, the channels relative to the start address can be scrolled through with the menu knob. The three knobs change the according channel shown in the ui. They have a step of 5 and a step of 1 when they are pressed.

```
 <   DMX Tester     
 Addr:  1  Channels                     
< 1       2      3 >
  0      35    220
```
