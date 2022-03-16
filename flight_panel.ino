#include <Joystick.h>

#include <SimpleRotary.h>
#include <Mouse.h>

SimpleRotary rotary(0,1,3);

//JOYSTICK SETTINGS
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK,
  4, //number of buttons
  0, //number of hat switches
  //Set as many axis to "true" as you have potentiometers for
  false, // y axis
  false, // x axis
  false, // z axis
  false, // rx axis
  false, // ry axis
  false, // rz axis
  false, // rudder
  false, // throttle
  false, // accelerator
  false, // brake
  false); // steering wheel

void setup(){
  Serial.begin(9600);
  Mouse.begin();
  Joystick.begin();
}

void loop(){
  byte i;
  i = rotary.rotate();
  
  // CW
  if ( i == 1 ) {
    Serial.println("CW");
    Joystick.setButton(1, 1); delay(50); Joystick.setButton(1, 0);
  }
  
  // CCW
  if ( i == 2 ) {
    Serial.println("CCW");
    Joystick.setButton(2, 1); delay(50); Joystick.setButton(2, 0);
  }
}
