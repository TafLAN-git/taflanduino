#include "HID-Project.h"

/*
TäfLAN arkadmaskinens arduinon finns flashade med denna sketch.

För att kompilera den med Arduinons IDE måste du installera HID
biblioteket härifrån: https://github.com/NicoHood/HID

Märk väl att i skrivande stund kräver biblioteket en Arduino IDE
version på minst 1.6.8, vilket då betydde en hourly version av
IDEn: https://www.arduino.cc/en/Main/Software

Använd Arduino typen "Arduino/Genuino Micro" då du flashar
Arduinon.
*/

void setup() {
  /** input mapping, 16 inputs in total:
   *
   *  D2: button 0
   *  D3: button 1
   *  D4: button 2
   *  D5: button 3
   *  D6: button 4
   *  D7: button 5
   *  D8: button 6
   *  D9: button 7
   *  D10: button 8
   *  D11: button 9
   *  D12: button 10
   *  D13: button 11
   *
   *  A0: hat 0 left
   *  A1: hat 0 down
   *  A2: hat 0 up
   *  A3: hat 0 right
   */

  // set the digital pins 2-13 as inputs
  for (int i = 2; i <= 13; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  // set the analog pins A0-A3 as inputs
  for (int i = A0; i <= A3; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  // init gamepad library
  Gamepad.begin();
}

bool buttons[16] = {false};

double hue = 0;
void loop() {
  Gamepad.releaseAll();

  // read state of buttons
  for (byte i = 2; i <= 13; i++) {
    int button = i - 2;

    bool pressed = !digitalRead(i);

    buttons[button] = pressed;

    if (pressed) {
      Gamepad.press(button + 1);
    }
  }

  bool right = false;
  bool up = false;
  bool down = false;
  bool left = false;

  // read state of directional input
  left  = !digitalRead(A0);
  down  = !digitalRead(A1);
  up    = !digitalRead(A2);
  right = !digitalRead(A3);

  if (up && right) {
    Gamepad.dPad2(GAMEPAD_DPAD_UP_RIGHT);
  } else if (up && left) {
    Gamepad.dPad2(GAMEPAD_DPAD_UP_LEFT);
  } else if (down && right) {
    Gamepad.dPad2(GAMEPAD_DPAD_DOWN_RIGHT);
  } else if (down && left) {
    Gamepad.dPad2(GAMEPAD_DPAD_DOWN_LEFT);
  } else if (up) {
    Gamepad.dPad2(GAMEPAD_DPAD_UP);
  } else if (down) {
    Gamepad.dPad2(GAMEPAD_DPAD_DOWN);
  } else if (right) {
    Gamepad.dPad2(GAMEPAD_DPAD_RIGHT);
  } else if (left) {
    Gamepad.dPad2(GAMEPAD_DPAD_LEFT);
  } else {
    Gamepad.dPad2(GAMEPAD_DPAD_CENTERED);
  }

  Gamepad.write();
}
