/*
 * Arduino Stream Deck with Real-Time Feedback
 * 
 * Receives status updates from companion Python script via serial
 * and updates LED colors accordingly. Combines button input with
 * visual feedback for Spotify, volume, and mute state.
 * 
 * Compatible with: led_upgrade_example.ino + realtime_companion.py
 */

#include <Keyboard.h>
#include <FastLED.h>

// LED Configuration
#define NUM_LEDS 12
#define DATA_PIN 10
#define LED_BRIGHTNESS 80

// Button pins
const int pinPrev = 5, pinPlay = 6, pinNext = 7;
const int pinSpotify = 8, pinAMD = 9, pinSteam = 10;

// LED indices
#define LED_PREV     0
#define LED_PLAY     1
#define LED_NEXT     2
#define LED_SPOTIFY  3
#define LED_AMD      4
#define LED_STEAM    5
#define LED_MUTE     6
#define LED_VOL_START 7  // LEDs 7-11 = volume bar

CRGB leds[NUM_LEDS];

// Serial command protocol (matches Python companion script)
#define CMD_SPOTIFY_PLAYING  'P'
#define CMD_SPOTIFY_PAUSED   'p'
#define CMD_SPOTIFY_STOPPED  'S'
#define CMD_MUTE_ON          'M'
#define CMD_MUTE_OFF         'm'

// Media HID codes
#define PLAY_PAUSE 0xCD
#define NEXT       0xB5
#define PREV       0xB6

const int debounce = 50;

void setup() {
  // Initialize USB serial (for debugging)
  Serial.begin(115200);
  Serial.println("Stream Deck initialized");
  
  Keyboard.begin();
  
  // Initialize FastLED
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  
  // Configure button pins
  pinMode(pinPrev, INPUT_PULLUP);
  pinMode(pinPlay, INPUT_PULLUP);
  pinMode(pinNext, INPUT_PULLUP);
  pinMode(pinSpotify, INPUT_PULLUP);
  pinMode(pinAMD, INPUT_PULLUP);
  pinMode(pinSteam, INPUT_PULLUP);
  
  // Set initial LED colors
  setIdleColors();
}

void loop() {
  // Check for serial commands from companion script
  handleSerialCommands();
  
  // Handle button presses
  handleButtons();
}

void handleSerialCommands() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    switch(command) {
      case CMD_SPOTIFY_PLAYING:
        leds[LED_SPOTIFY] = CRGB::Green;  // Green = playing
        FastLED.show();
        break;
        
      case CMD_SPOTIFY_PAUSED:
        leds[LED_SPOTIFY] = CRGB::Orange;  // Orange = paused
        FastLED.show();
        break;
        
      case CMD_SPOTIFY_STOPPED:
        leds[LED_SPOTIFY] = CRGB(0, 20, 0);  // Dim green = stopped
        FastLED.show();
        break;
        
      case CMD_MUTE_ON:
        leds[LED_MUTE] = CRGB::Red;  // Red = muted
        FastLED.show();
        break;
        
      case CMD_MUTE_OFF:
        leds[LED_MUTE] = CRGB::Black;  // Off = unmuted
        FastLED.show();
        break;
        
      default:
        // Volume level (0-100)
        if(command >= 0 && command <= 100) {
          updateVolumeBar(command);
        }
        break;
    }
  }
}

void handleButtons() {
  // Previous track
  if (digitalRead(pinPrev) == LOW) {
    flashButton(LED_PREV, CRGB::White, CRGB::Blue);
    Keyboard.press(PREV);
    delay(debounce);
    Keyboard.releaseAll();
    delay(200);
  }

  // Play/Pause
  if (digitalRead(pinPlay) == LOW) {
    flashButton(LED_PLAY, CRGB::White, CRGB::Blue);
    Keyboard.press(PLAY_PAUSE);
    delay(debounce);
    Keyboard.releaseAll();
    delay(200);
  }

  // Next track
  if (digitalRead(pinNext) == LOW) {
    flashButton(LED_NEXT, CRGB::White, CRGB::Blue);
    Keyboard.press(NEXT);
    delay(debounce);
    Keyboard.releaseAll();
    delay(200);
  }

  // Spotify - Win+4
  if (digitalRead(pinSpotify) == LOW) {
    flashButton(LED_SPOTIFY, CRGB::White, CRGB::Green);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('4');
    delay(100);
    Keyboard.releaseAll();
    delay(300);
  }

  // AMD Adrenaline - Alt+R
  if (digitalRead(pinAMD) == LOW) {
    flashButton(LED_AMD, CRGB::White, CRGB::Red);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(300);
  }

  // Steam - Win+2
  if (digitalRead(pinSteam) == LOW) {
    flashButton(LED_STEAM, CRGB::White, CRGB::Purple);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('2');
    delay(100);
    Keyboard.releaseAll();
    delay(300);
  }
}

void setIdleColors() {
  // Media controls - blue
  leds[LED_PREV] = CRGB::Blue;
  leds[LED_PLAY] = CRGB::Blue;
  leds[LED_NEXT] = CRGB::Blue;
  
  // Application launchers
  leds[LED_SPOTIFY] = CRGB(0, 20, 0);  // Dim green (will update based on state)
  leds[LED_AMD] = CRGB::Red;
  leds[LED_STEAM] = CRGB::Purple;
  
  // Mute indicator (off by default)
  leds[LED_MUTE] = CRGB::Black;
  
  // Volume bar (will update based on system volume)
  for(int i = LED_VOL_START; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();
}

void flashButton(int ledIndex, CRGB flashColor, CRGB returnColor) {
  leds[ledIndex] = flashColor;
  FastLED.show();
  delay(50);
  leds[ledIndex] = returnColor;
  FastLED.show();
}

void updateVolumeBar(uint8_t volumePercent) {
  // Show volume on 5 LEDs (7-11) as a bar graph
  int numLEDs = map(volumePercent, 0, 100, 0, 5);
  
  for(int i = 0; i < 5; i++) {
    if(i < numLEDs) {
      // Color gradient: green (low) → yellow (mid) → red (high)
      if(volumePercent < 30) {
        leds[LED_VOL_START + i] = CRGB::Green;
      } else if(volumePercent < 70) {
        leds[LED_VOL_START + i] = CRGB::Yellow;
      } else {
        leds[LED_VOL_START + i] = CRGB::Red;
      }
    } else {
      leds[LED_VOL_START + i] = CRGB::Black;
    }
  }
  
  FastLED.show();
}

/*
 * Usage Instructions:
 * 
 * 1. Upload this sketch to Arduino
 * 2. Note the COM port (Tools → Port)
 * 3. Update SERIAL_PORT in realtime_companion.py to match
 * 4. Run Python script: python realtime_companion.py
 * 5. LEDs will now show real-time Spotify and volume status
 * 
 * Troubleshooting:
 * - If LEDs don't update: Check serial port in Python script
 * - If buttons don't work: Check pin assignments
 * - If colors wrong: Verify FastLED color order (GRB vs RGB)
 */
