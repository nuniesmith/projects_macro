/*
 * ESP32 Wireless Macro Keyboard
 * * Features: 
 * - Bluetooth Low Energy (BLE) Keyboard for media/shortcuts
 * - Wi-Fi connection for IoT/Smart Home triggers
 * * Hardware: ESP32 Dev Module
 * Libraries: BleKeyboard, WiFi, HTTPClient
 */

#include <BleKeyboard.h>
#include <WiFi.h>
#include <HTTPClient.h>

// --- CONFIGURATION ---
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
BleKeyboard bleKeyboard("Jordan's MacroPad", "ESP32", 100);

const int debounce = 50;  // ms

// --- PIN DEFINITIONS (ESP32 GPIOs) ---
// Note: ESP32 pins differ from Pro Micro. 
// Avoid GPIO 6-11 (connected to internal flash).
// Input only pins: 34, 35, 36, 39 (No internal pull-ups!)
const int pinPrev = 15, pinPlay = 2, pinNext = 4;
const int pinSpotify = 16, pinAMD = 17, pinSteam = 5;
// Example Wi-Fi Action Button (replaces one of your previous buttons or add new)
const int pinSmartAction = 18; 

// --- STATE VARIABLES ---
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(115200);

  // Configure Pins
  // ESP32 INPUT_PULLUP is safer than internal pullups on some pins,
  // but verify your specific board's pinout.
  pinMode(pinPrev, INPUT_PULLUP);
  pinMode(pinPlay, INPUT_PULLUP);
  pinMode(pinNext, INPUT_PULLUP);
  pinMode(pinSpotify, INPUT_PULLUP);
  pinMode(pinAMD, INPUT_PULLUP);
  pinMode(pinSteam, INPUT_PULLUP);
  pinMode(pinSmartAction, INPUT_PULLUP);

  // Start Bluetooth
  Serial.println("Starting BLE...");
  bleKeyboard.begin();

  // Start Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  // Non-blocking WiFi connection check (optional)
  // We won't wait here so keyboard works immediately
}

void loop() {
  // Only send keystrokes if Bluetooth is connected
  if (bleKeyboard.isConnected()) {
    
    // --- MEDIA CONTROLS ---
    checkButton(pinPrev, KEY_MEDIA_PREVIOUS_TRACK);
    checkButton(pinPlay, KEY_MEDIA_PLAY_PAUSE);
    checkButton(pinNext, KEY_MEDIA_NEXT_TRACK);

    // --- APP LAUNCHERS ---
    
    // Spotify (Win + 4)
    if (isPressed(pinSpotify)) {
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.print("4");
      delay(100);
      bleKeyboard.releaseAll();
      delay(300);
    }

    // AMD (Alt + R)
    if (isPressed(pinAMD)) {
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.print("r");
      delay(100);
      bleKeyboard.releaseAll();
      delay(300);
    }

    // Steam (Win + 2)
    if (isPressed(pinSteam)) {
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.print("2");
      delay(100);
      bleKeyboard.releaseAll();
      delay(300);
    }
  }

  // --- WIFI ACTION ---
  // This works even if Bluetooth is disconnected, as long as WiFi is up
  if (isPressed(pinSmartAction)) {
    performWebAction();
  }
}

// Helper for simple single-key media buttons
void checkButton(int pin, uint8_t key) {
  if (digitalRead(pin) == LOW) {
    bleKeyboard.write(key);
    delay(300); // Simple debounce/repeat prevention
  }
}

// Helper to clean up the digitalRead check
bool isPressed(int pin) {
  if (digitalRead(pin) == LOW) {
    delay(debounce); // Debounce
    if (digitalRead(pin) == LOW) {
      return true;
    }
  }
  return false;
}

// Function to trigger a web request via Wi-Fi
void performWebAction() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    Serial.println("Triggering Smart Action...");
    
    // Example: Call a webhook (e.g., IFTTT, Home Assistant, or a custom Server)
    http.begin("https://api.example.com/trigger-lights"); 
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
    delay(500); // Prevent spamming the API
  } else {
    Serial.println("WiFi not connected!");
  }
}
