/*
 * WS2812B RGB LED Upgrade Example
 * 
 * Adds individually addressable RGB LEDs to your stream deck for
 * color-coded visual feedback. Compatible with existing button code.
 * 
 * Hardware Required:
 * - WS2812B LED strip (12-30 LEDs)
 * - 330Ω resistor (data line protection)
 * - 1000µF capacitor (power filtering, optional but recommended)
 * 
 * Library Required:
 * - FastLED (install via Arduino Library Manager)
 */

#include <Keyboard.h>
#include <FastLED.h>

// LED Configuration
#define NUM_LEDS 12        // Match your button count
#define DATA_PIN 10        // WS2812B data line
#define LED_BRIGHTNESS 80  // 0-255 (start conservative to avoid overheating)

// Button pins (from your existing project)
const int pinPrev = 5, pinPlay = 6, pinNext = 7;
const int pinSpotify = 8, pinAMD = 9, pinSteam = 10;

// LED array
CRGB leds[NUM_LEDS];

// LED indices (map buttons to LEDs)
#define LED_PREV     0
#define LED_PLAY     1
#define LED_NEXT     2
#define LED_SPOTIFY  3
#define LED_AMD      4
#define LED_STEAM    5

// Media HID codes
#define VOL_UP     0xE9
#define VOL_DOWN   0xEA
#define MUTE       0xE2
#define PLAY_PAUSE 0xCD
#define NEXT       0xB5
#define PREV       0xB6

const int debounce = 50;  // ms

void setup() {
  Keyboard.begin();
  
  // Initialize FastLED
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  
  // Configure button pins with internal pull-ups
  pinMode(pinPrev, INPUT_PULLUP);
  pinMode(pinPlay, INPUT_PULLUP);
  pinMode(pinNext, INPUT_PULLUP);
  pinMode(pinSpotify, INPUT_PULLUP);
  pinMode(pinAMD, INPUT_PULLUP);
  pinMode(pinSteam, INPUT_PULLUP);
  
  // Set initial LED colors (idle state)
  setIdleColors();
}

void loop() {
  // Previous track
  if (digitalRead(pinPrev) == LOW) {
    leds[LED_PREV] = CRGB::White;  // Flash white on press
    FastLED.show();
    
    Keyboard.press(PREV);
    delay(debounce);
    Keyboard.releaseAll();
    
    leds[LED_PREV] = CRGB::Blue;  // Back to blue (media control color)
    FastLED.show();
    delay(200);
  }

  // Play/Pause
  if (digitalRead(pinPlay) == LOW) {
    leds[LED_PLAY] = CRGB::White;
    FastLED.show();
    
    Keyboard.press(PLAY_PAUSE);
    delay(debounce);
    Keyboard.releaseAll();
    
    leds[LED_PLAY] = CRGB::Blue;
    FastLED.show();
    delay(200);
  }

  // Next track
  if (digitalRead(pinNext) == LOW) {
    leds[LED_NEXT] = CRGB::White;
    FastLED.show();
    
    Keyboard.press(NEXT);
    delay(debounce);
    Keyboard.releaseAll();
    
    leds[LED_NEXT] = CRGB::Blue;
    FastLED.show();
    delay(200);
  }

  // Spotify - Win+4 (adjust to match your taskbar position)
  if (digitalRead(pinSpotify) == LOW) {
    leds[LED_SPOTIFY] = CRGB::White;
    FastLED.show();
    
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('4');
    delay(100);
    Keyboard.releaseAll();
    
    leds[LED_SPOTIFY] = CRGB::Green;  // Green for Spotify
    FastLED.show();
    delay(300);
  }

  // AMD Adrenaline - Alt+R
  if (digitalRead(pinAMD) == LOW) {
    leds[LED_AMD] = CRGB::White;
    FastLED.show();
    
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    
    leds[LED_AMD] = CRGB::Red;  // Red for AMD
    FastLED.show();
    delay(300);
  }

  // Steam - Win+2 (adjust to match your taskbar position)
  if (digitalRead(pinSteam) == LOW) {
    leds[LED_STEAM] = CRGB::White;
    FastLED.show();
    
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('2');
    delay(100);
    Keyboard.releaseAll();
    
    leds[LED_STEAM] = CRGB::Purple;  // Purple for Steam
    FastLED.show();
    delay(300);
  }
  
  // Optional: Breathing effect on unused LEDs
  breathingEffect();
}

void setIdleColors() {
  // Media controls - blue
  leds[LED_PREV] = CRGB::Blue;
  leds[LED_PLAY] = CRGB::Blue;
  leds[LED_NEXT] = CRGB::Blue;
  
  // Application launchers - brand colors
  leds[LED_SPOTIFY] = CRGB::Green;
  leds[LED_AMD] = CRGB::Red;
  leds[LED_STEAM] = CRGB::Purple;
  
  // Remaining LEDs - dim white underglow
  for(int i = 6; i < NUM_LEDS; i++) {
    leds[i] = CRGB(10, 10, 10);
  }
  
  FastLED.show();
}

void breathingEffect() {
  // Optional: Subtle breathing on unused LEDs for ambient effect
  static uint8_t brightness = 0;
  static int8_t direction = 1;
  static unsigned long lastUpdate = 0;
  
  if(millis() - lastUpdate > 20) {  // Update every 20ms
    brightness += direction;
    if(brightness == 0 || brightness == 50) {
      direction *= -1;
    }
    
    // Apply breathing to underglow LEDs only (6-11)
    for(int i = 6; i < NUM_LEDS; i++) {
      leds[i] = CHSV(160, 255, brightness);  // Cyan breathing
    }
    
    FastLED.show();
    lastUpdate = millis();
  }
}

/*
 * Color Scheme Ideas:
 * 
 * Media Controls:
 * - Previous/Play/Next: Blue (standard media color)
 * 
 * Applications:
 * - Spotify: Green (#1DB954)
 * - Discord: Purple (#5865F2)
 * - OBS: Red (#FF0000)
 * - Steam: Blue-purple (#171a21)
 * - Chrome: Red/Yellow/Green/Blue (Google colors)
 * 
 * Volume:
 * - Volume Up: Green
 * - Volume Down: Green
 * - Mute: Red
 * 
 * System:
 * - Lock Screen: Red
 * - Sleep: Orange
 * - Shutdown: Dark Red
 */
