#include <MatrixKeypad.h>
#include <Joystick.h>
#include <SimpleRotary.h>

const uint8_t rown = 1; //4 rows
const uint8_t coln = 2; //3 columns
uint8_t rowPins[rown] = {4}; 
uint8_t colPins[coln] = {2, 3};
char keymap[rown][coln] = 
  {{2,3,}};

MatrixKeypad_t *keypad;

SimpleRotary rotary(0,1,8);

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
  Joystick.begin();
  keypad = MatrixKeypad_create((char*)keymap /* don't forget to do this cast */, rowPins, colPins, rown, coln); //creates the keypad object
}

void loop(){
  process_rotary();
  process_keys();
}

void process_rotary() {
  byte i;
  i = rotary.rotate();
  
  // CW
  if ( i == 1 ) {
    Serial.println("CW");
    button_click(0);
  }
  
  // CCW
  if ( i == 2 ) {
    Serial.println("CCW");
    button_click(1);
  }
}

void process_keys() {
  MatrixKeypad_scan(keypad); //scans for a key press event
  if(MatrixKeypad_hasKey(keypad)){ //if a key was pressed
    char key = MatrixKeypad_getKey(keypad); //get the key
    Serial.println(key, DEC); //prints the pressed key to the serial output
    button_click(key);
  }
}

void button_click(int button_num){
  Joystick.setButton(button_num, 1); delay(50); Joystick.setButton(button_num, 0);
}
