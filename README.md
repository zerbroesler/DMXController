# DMXController
An Arduino Mega DMX Controller with LCD Display

This is the software / documentation part of the arduino dmx controller project.

# Hardware
Arduino mega
4 rotary encoders
1 LCD display 20x4 characters with I2c connector
RS485 encoder with XLR connector to connect DMX devices (Lamps)
Schematics follow...

# Software
It is mainly an ui which uses an 20x4 characters display and some rotaty encoders / buttons.

# UI
The UI shows menus which lead to other menus. This is needed due to the lack of space on the display.
The 4th row is usually used to show the values of the three rotary encoders directly below the display. They usually show RGB or HSV values.
