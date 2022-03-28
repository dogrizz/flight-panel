# flight-panel

## Code
Code to support my Arduino flight panel

Dependencies:
 - https://github.com/MHeironimus/ArduinoJoystickLibrary
 - https://github.com/mprograms/SimpleRotary
 - https://github.com/victorsvi/MatrixKeypad

## Panel
Panel is supposed to fit inside Thrustmaster Flying Clamp

## Buttons used
 - Momentary Push Button Switch Square SPST 1 NO 1 NC
 - SPDT 3P on-(on) momentary switch (use 2,3 connectors)
 - EC16 encoders
 - Adafruit 3219 for the Master Switch ;)
### Adafruit connection
To get light only when turned on:
 - fs_current_pin to +
 - fs_input_pin to =D
 - ground to ground :)
