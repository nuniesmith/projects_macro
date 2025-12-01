/*
 * Arduino Macro Keyboard
 * 
 * A USB HID macro keyboard and media controller using Arduino Pro Micro.
 * Features: media controls, volume encoder, application launcher buttons.
 * 
 * Hardware: Arduino Pro Micro (5V/16MHz)
 * Libraries: Keyboard (built-in)
 */

#include <Keyboard.h>

const int debounce = 50;  // ms

// Button pins
const int pinPrev = 5, pinPlay = 6, pinNext = 7;
const int pinSpotify = 8, pinAMD = 9, pinSteam = 10;

// LED pins (optional)
const int ledPrev = 18, ledPlay = 19, ledNext = 21;

// Media HID codes (work on Windows/Mac/Linux)
#define VOL_UP     0xE9
#define VOL_DOWN   0xEA
#define MUTE       0xE2
#define PLAY_PAUSE 0xCD
#define NEXT       0xB5
#define PREV       0xB6

void setup() {
  Keyboard.begin();
  
  // Configure button pins with internal pull-ups
  pinMode(pinPrev, INPUT_PULLUP);
  pinMode(pinPlay, INPUT_PULLUP);
  pinMode(pinNext, INPUT_PULLUP);
  pinMode(pinSpotify, INPUT_PULLUP);
  pinMode(pinAMD, INPUT_PULLUP);
  pinMode(pinSteam, INPUT_PULLUP);
  
  // Configure LED pins
  pinMode(ledPrev, OUTPUT);
  pinMode(ledPlay, OUTPUT);
  pinMode(ledNext, OUTPUT);
}

void loop() {
  // Previous track
  if (digitalRead(pinPrev) == LOW) {
    Keyboard.press(PREV);
    digitalWrite(ledPrev, HIGH);
    delay(debounce);
    Keyboard.releaseAll();
    digitalWrite(ledPrev, LOW);
    delay(200);  // simple debounce + prevent repeat
  }

  // Play/Pause
  if (digitalRead(pinPlay) == LOW) {
    Keyboard.press(PLAY_PAUSE);
    digitalWrite(ledPlay, HIGH);
    delay(debounce);
    Keyboard.releaseAll();
    digitalWrite(ledPlay, LOW);
    delay(200);
  }

  // Next track
  if (digitalRead(pinNext) == LOW) {
    Keyboard.press(NEXT);
    digitalWrite(ledNext, HIGH);
    delay(debounce);
    Keyboard.releaseAll();
    digitalWrite(ledNext, LOW);
    delay(200);
  }

  // Spotify (taskbar position 4 example → Win+4)
  // Adjust the number to match your taskbar position
  if (digitalRead(pinSpotify) == LOW) {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('4');
    delay(100);
    Keyboard.releaseAll();
    delay(300);
  }

  // AMD Adrenaline – default global hotkey is Alt+R for overlay
  // Change to Ctrl+Shift+A for settings if preferred
  if (digitalRead(pinAMD) == LOW) {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(300);
  }

  // Steam – many people use Ctrl+Shift+S or taskbar Win+2
  // Adjust to match your taskbar position
  if (digitalRead(pinSteam) == LOW) {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('2');
    delay(100);
    Keyboard.releaseAll();
    delay(300);
  }
}

/*
 * TODO: Add rotary encoder support for volume control
 * 
 * Rotary encoder wiring:
 * - CLK → Pin 0 (interrupt capable)
 * - DT → Pin 1 (interrupt capable)
 * - SW → Pin 14 (A0) for mute toggle
 * - + → 5V
 * - GND → GND
 * 
 * Use Encoder library or interrupt-based reading for smooth volume control.
 */

