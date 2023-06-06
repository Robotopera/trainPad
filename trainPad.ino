#include <Joystick.h>

// set pin numbers for inputs:
const int regPin = 17;  // Regulator -> Throttle
const int revPin = 18;  // Reverser  -> Accelerator
const int brakePin = 19;  // Brake     -> Brake
const int whistlePin = 20;  // Whistle   -> X
const int generatorPin = 11;  // Generator -> Y
const int compressorPin = 12;  //Compressor -> Z
const int modPin = 5;   //Joystick.setButton(0, currentButtonState);
const int bellPin = 6;   //Joystick.setButton(1, currentButtonState)
const int sandPin = 7;   //Joystick.setButton(2, currentButtonState)
const int cockPin = 8;   //Joystick.setButton(3, currentButtonState)
const int delayVal = 400;

//create joystick object
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, true,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, true,          // No rudder or throttle
  true, true, false);  // No accelerator, brake, or steering

//create state objects

int currentButtonState[4];
//int lastButtonState[4];
int currentSliderState[6];
//int lastSliderState[6];
int buttonMap[4];
int sliderMap[6];

void readButtons(){
  //lastButtonState = currentButtonState;
  for (int button = 0; button < 4; button++)
  {
    currentButtonState[button] = digitalRead(buttonMap[button]);
  }
}

void readSliders(){
  //lastSliderState = currentSliderState;
  for (int slider = 0; slider < 6; slider++)
  {
    currentSliderState[slider] = analogRead(sliderMap[slider])/4; //divide by 4 to convert 10 bit value to 8 bit value
  }
}

void setup() { // initialize the buttons' inputs:
  pinMode(modPin, INPUT_PULLUP);
  pinMode(bellPin, INPUT_PULLUP);
  pinMode(sandPin, INPUT_PULLUP);
  pinMode(cockPin, INPUT_PULLUP);
  int currentButtonState[4] = {0,0,0,0};
  int lastButtonState[4] = {0,0,0,0};
  int buttonMap[4] = {modPin,bellPin,sandPin,cockPin};
  int currentSliderState[6] = {0,0,0,0,0,0};
  int lastSliderState[6] = {0,0,0,0,0,0};
  int sliderMap[6] = {regPin,revPin,brakePin,whistlePin,generatorPin,compressorPin};

  Joystick.begin();  
  Joystick.setThrottleRange(0, 255);
  Joystick.setAcceleratorRange(-127, 127);
  Joystick.setBrakeRange(0, 255);
  Joystick.setXAxisRange(0, 255);
  Joystick.setYAxisRange(0, 255);
  Joystick.setZAxisRange(0, 255);
}

void loop() {
  readButtons();
  readSliders();
  for (int button = 0; button < 4; button++){
    Joystick.setButton(button, currentButtonState[button]);
  }
  Joystick.setThrottle(currentSliderState[0]);
  Joystick.setAccelerator(128 - currentSliderState[1]);
  Joystick.setBrake(currentSliderState[2]);
  Joystick.setXAxis(currentSliderState[3]);
  Joystick.setYAxis(currentSliderState[4]);
  Joystick.setZAxis(currentSliderState[5]);
 }
