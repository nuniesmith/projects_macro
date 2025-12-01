# Upgrade Quick Reference

**Quick reference card for upgrading your stream deck. See [upgrade_roadmap.md](upgrade_roadmap.md) for full details.**

---

## 🎯 Upgrade Sequence (Recommended Order)

```
Current Build (v1.0)
    ↓ 1 weekend, $5-15
[1] WS2812B RGB LEDs
    ↓ 1 weekend, free
[2] Real-Time Status Feedback
    ↓ 2-3 days, $25-60
[3] Nextion Touchscreen Display
    ↓ 1-2 weeks, $30-60
[4] Custom PCB Design
    ↓ 1 week, $10-30
[5] 3D-Printed Enclosure
    ↓
Final Build (v2.0) - Total: $70-165
```

---

## 📋 At-a-Glance Comparison

| Upgrade | Time | Cost | Difficulty | Impact |
|---------|------|------|------------|--------|
| WS2812B LEDs | 1 weekend | $5-15 | ⭐ Easy | 🔥 High |
| Real-time Status | 1 weekend | Free | ⭐ Easy | 🔥 High |
| Nextion Display | 2-3 days | $25-60 | ⭐⭐ Medium | 🔥🔥 Very High |
| Custom PCB | 1-2 weeks | $30-60 | ⭐⭐⭐ Medium | 🔥🔥 Very High |
| 3D Case | 1 week | $10-30 | ⭐⭐ Medium | 🔥 High |

---

## 🛠️ Upgrade 1: WS2812B RGB LEDs

**What You Need:**
- WS2812B LED strip (12-30 LEDs) - $5-15
- 330Ω resistor - $0.05
- 1000µF capacitor (optional) - $0.50

**Wiring:**
```
Pro Micro Pin 10 → 330Ω → WS2812B Data In
5V → LED Strip 5V
GND → LED Strip GND
```

**Code:**
```cpp
#include <FastLED.h>
#define NUM_LEDS 12
#define DATA_PIN 10
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(80);
}

// Turn LED 0 green
leds[0] = CRGB::Green;
FastLED.show();
```

**See:** `examples/led_upgrade_example.ino`

---

## 🛠️ Upgrade 2: Real-Time Status

**What You Need:**
- Python 3.x (free)
- Libraries: `pip install spotipy pyserial pycaw-python pywin32`

**Arduino Side:**
```cpp
void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'P') leds[LED_SPOTIFY] = CRGB::Green;  // Playing
    if (cmd == 'p') leds[LED_SPOTIFY] = CRGB::Orange; // Paused
    FastLED.show();
  }
}
```

**PC Side:**
```python
import serial, spotipy
ser = serial.Serial('COM3', 115200)

while True:
    current = sp.current_playback()
    if current and current['is_playing']:
        ser.write(b'P')  # Send "Playing" to Arduino
    time.sleep(1)
```

**See:** `examples/realtime_companion.py` + `examples/arduino_with_feedback.ino`

---

## 🛠️ Upgrade 3: Nextion Display

**What You Need:**
- Nextion 3.5" Basic NX4832K035 - $25-35
- Nextion Editor (free download)

**Wiring:**
```
Nextion TX (Yellow) → Pro Micro Pin 0 (RX)
Nextion RX (Blue) → Pro Micro Pin 1 (TX)
Nextion VCC (Red) → 5V
Nextion GND (Black) → GND
```

**Arduino Code:**
```cpp
void setup() {
  Serial1.begin(9600);  // Hardware serial for Nextion
  sendNextionCommand("page 0");
}

void sendNextionCommand(String cmd) {
  Serial1.print(cmd);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
}
```

**Design GUI:**
1. Download Nextion Editor
2. Create 3.5" project
3. Add buttons with icons
4. Export .tft file to microSD
5. Insert microSD into Nextion, power on to flash

**Resources:**
- Hackster project (March 2025): Complete example with icons
- Instructables Nextion guide: GUI design tutorial

---

## 🛠️ Upgrade 4: Custom PCB

**What You Need:**
- KiCad 8 (free)
- PCB fabrication: JLCPCB - $12 for 5 boards
- Components: hotswap sockets, switches, LEDs - $30-60

**Design Process:**
1. Clone template: Hackster Nextion Stream Deck KiCad files
2. Customize layout (row/column count)
3. Export Gerber files
4. Upload to JLCPCB
5. Wait 2-3 weeks for delivery

**Essential PCB Features:**
- Pro Micro footprint (or direct ATmega32U4)
- Kailh hotswap socket footprints
- WS2812B LED footprints under switches
- Mounting holes (M3, 3mm diameter)

**Templates:**
- Hackster project (2025) - 3×4 with Nextion
- BDN9 by keeb.io - 3×3 macropad
- GitHub: search "macropad kicad pro micro"

---

## 🛠️ Upgrade 5: 3D-Printed Case

**What You Need:**
- 3D printer access
- PLA filament - $15-20/kg
- Heat-set inserts (M3 × 4mm) - $5
- Screws (M3 × 8mm) - $2

**Design Options:**

**Option A: Use existing design**
- Thingiverse: "stream deck pro micro"
- Printables: "macropad nextion"
- Super Make Something cases (most popular)

**Option B: Parametric generator**
- Swillkb Plate Builder: http://builder.swillkb.com/
- Enter your layout → get STL files

**Option C: Design your own**
- Fusion 360 / OnShape
- Measure PCB dimensions
- Design around components

**Print Settings:**
```
Layer Height: 0.2mm
Infill: 20-30%
Walls: 3-4
Top/Bottom: 5 layers
Supports: Only for >60° overhangs

Switch Plate CRITICAL:
- Exactly 1.5mm thick
- 100% infill
```

---

## 📊 Cost Breakdown

### Budget Build ($41 total)
- Pro Micro: $5
- Nextion 3.5": $28
- WS2812B underglow: $8
- Python script: Free
- 3D case (Thingiverse): Free

**Result:** Works better than $150 Elgato

---

### Premium Build ($93 total)
- Pro Micro: $5
- Nextion 3.5" Enhanced: $38
- Custom PCB: $12 (for 5)
- Hotswap sockets: $1.20
- Gateron switches: $6
- WS2812B SMD: $1.20
- Keycaps: $15
- 3D case + hardware: $15

**Result:** Professional quality, fully custom

---

## 🎓 Learning Resources

### Beginner-Friendly
- ✅ Hackster Nextion project (March 2025) - **Start here!**
- ✅ Random Nerd Tutorials: WS2812B guide
- ✅ Adafruit NeoPixel Überguide

### Intermediate
- ⚙️ Getting to Blinky (Phil's Lab) - KiCad tutorial
- ⚙️ ai03 Keyboard PCB Guide - Industry standard
- ⚙️ Nextion Instruction Set - Command reference

### Advanced
- 🔧 KiCad footprint libraries for MX switches
- 🔧 JLCPCB assembly service (SMT components)
- 🔧 Direct ATmega32U4 design (no Pro Micro)

---

## 🐛 Common Issues

| Problem | Solution |
|---------|----------|
| WS2812B not working | Try different color order: GRB, RGB, BRG |
| Nextion blank screen | Check TX→RX, RX→TX crossed, verify baud rate |
| Python script no connect | Wrong COM port, check Device Manager |
| PCB too expensive | Order with friends, split 5-board minimum |
| 3D print warping | Use bed adhesion, slow first layer |

---

## ✅ Recommended "Final Form" (2025)

Based on 100+ community builds in 2024-2025:

**Hardware:**
- Arduino Pro Micro ($5)
- Nextion 3.5" touchscreen ($28)
- Custom PCB with hotswap sockets ($12 + $30 components)
- 12× Gateron switches ($6)
- 12× WS2812B underglow ($1.20)
- 3D-printed parametric case ($15)

**Software:**
- Arduino sketch with FastLED + Nextion
- Python companion script (Spotify + volume)
- Custom Nextion GUI with icons

**Total Cost:** $97.20
**Total Time:** 4-6 weeks (working weekends)
**Result:** Better than $150 Elgato Stream Deck

---

## 📚 Full Documentation

For detailed guides, wiring diagrams, code examples, and troubleshooting:

👉 **See [upgrade_roadmap.md](upgrade_roadmap.md)**

For working code examples:

👉 **See `../examples/` directory**

---

**Last Updated:** December 2025
