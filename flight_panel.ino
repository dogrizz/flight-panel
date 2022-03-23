#include <MatrixKeypad.h>
#include <Joystick.h>
#include <SimpleRotary.h>

/** 
 Fireswitch setup 
 It isn't part of the matrix as it is bipositional essentially closing one row and column 
 making all other buttons on that useless.
**/
const uint8_t fs_pin = 8;
const int fs_poll_freq = 500; // ms
int fs_state = 0;
unsigned long fs_lastScan = 0;
const int fs_button = 20;

/** Keypad setup **/
const uint8_t rown = 4; 
const uint8_t coln = 4;
const uint8_t rowPins[rown] = {0,1,2,3}; 
const uint8_t colPins[coln] = {4,5,6,7};
const uint8_t key_scan_freq = 50; // ms
const uint8_t key_repeat_timeout = 200; // ms, how long before registering same key being pressed

const char keymap[rown][coln] = // keymap matrix mapping to joystick buttons
  {
    {4, 5, 6, 7},
    {8, 9, 10, 11},
    {12, 13, 14, 15},
    {16, 17, 18, 19}, // unnused
  };

MatrixKeypad_t *keypad;
unsigned long lastScan;
unsigned long lastKeyPress;
char prev_key;

/** Rotary setup **/
SimpleRotary rotary1(10, // first spin pin
                    11, // second spin pin
                    14  // push button pin - not processed
);
SimpleRotary rotary2(12, // first spin pin
                    13, // second spin pin
                    14  // push button pin - not processed
);

/** Joystick settings **/
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK,
  21, //number of buttons + number of rotaries * 2
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
  keypad = MatrixKeypad_create((char*)keymap, rowPins, colPins, rown, coln);
  pinMode(fs_pin, INPUT_PULLUP);
}

void loop(){
  process_keys();
  process_fire_switch();
  process_rotary(rotary1, 0, 1);
  process_rotary(rotary2, 2, 3);
}

void process_keys() {
  if(millis() - lastScan >= key_scan_freq) {
    lastScan = millis();
    MatrixKeypad_scan(keypad);
    
    if(MatrixKeypad_hasKey(keypad)){
      char key = MatrixKeypad_getKey(keypad);
      if(key != prev_key || millis() - lastKeyPress >= key_repeat_timeout) {
        button_click(key);
        lastKeyPress = millis();
        prev_key = key;
      }
    }
  }
}

void process_fire_switch() {
  if(millis() - fs_lastScan >= fs_poll_freq) {
    fs_lastScan = millis();
    int state = digitalRead(fs_pin);
    if (state != fs_state) { 
      fs_state = state;
      button_click(fs_button);
    }
  }
}

void process_rotary(SimpleRotary &rotary, uint8_t cw, uint8_t ccw) {
  byte i;
  i = rotary.rotate();
  
  if ( i == 1 ) {
    button_click(cw);
  }
  
  if ( i == 2 ) {
    button_click(ccw);
  }
}

void button_click(int button_num){
  Joystick.setButton(button_num, 1); delay(50); Joystick.setButton(button_num, 0);
  Serial.println(button_num, DEC);
}
