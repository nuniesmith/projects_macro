# Bill of Materials (BOM)

Complete component list for the Arduino Stream Deck project.

## Required Components

| Component | Quantity | Description | Approx. Cost |
|-----------|----------|-------------|--------------|
| Arduino Pro Micro | 1 | 5V/16MHz version (ATMega32U4) | $3–8 |
| Tactile Buttons | 9–12 | 6×6mm or 12×12mm momentary push buttons | $0.10–0.50 each |
| Rotary Encoder | 1 | KY-040 or EC11 with push switch | $1–3 |
| LEDs | 9–12 | 3mm or 5mm LEDs (any color) | $0.05–0.20 each |
| Resistors | 9–12 | 220Ω (1/4W) for LED current limiting | $0.01 each |
| Breadboard | 1 | Half-size or full-size for prototyping | $3–5 |
| Jumper Wires | ~20 | Male-to-male for breadboard connections | $2–5 |

**Total Estimated Cost: $15–35** (depending on component quality and source)

## Optional Components (for final build)

| Component | Quantity | Description | Approx. Cost |
|-----------|----------|-------------|--------------|
| Cherry MX Switches | 9–12 | Mechanical keyboard switches (or Gateron) | $0.50–1.50 each |
| Keycaps | 9–12 | MX-compatible keycaps | $0.50–2.00 each |
| WS2812B LED Strip | 1 | Individually addressable RGB LEDs (optional upgrade) | $5–10 |
| Perfboard/PCB | 1 | For permanent soldered build | $5–20 |
| Enclosure | 1 | 3D-printed or custom case | $10–30 |

## Component Details

### Arduino Pro Micro
- **Why this board?** Native USB HID support (ATMega32U4), no additional drivers needed
- **Alternatives:** SparkFun Pro Micro, cheap clones from AliExpress/Amazon
- **Important:** Must be 5V/16MHz version (not 3.3V/8MHz)

### Buttons
- **Breadboard:** Standard 6×6mm or 12×12mm tactile switches
- **Final build:** Cherry MX or Gateron switches for professional feel
- **No diodes needed:** Direct pin-to-GND wiring with internal pull-ups

### Rotary Encoder
- **KY-040:** Most common, includes push switch
- **EC11:** Alternative with better detent feel
- **Wiring:** CLK/DT to interrupt pins, SW to any digital pin

### LEDs
- **Breadboard:** Standard 3mm or 5mm LEDs with 220Ω resistors
- **Upgrade:** WS2812B strip for RGB color control (requires FastLED library)
- **Resistor calculation:** 220Ω is safe for 5V supply with most LEDs

## Where to Buy

- **AliExpress:** Cheapest for bulk components (long shipping)
- **Amazon:** Fast shipping, slightly higher prices
- **SparkFun/Adafruit:** Premium quality, good documentation
- **DigiKey/Mouser:** Professional components, best for final builds

## Notes

- All buttons use internal pull-ups (INPUT_PULLUP), so no external resistors needed
- LEDs require 220Ω resistors to limit current (prevents damage to Arduino pins)
- Rotary encoder is optional but highly recommended for professional feel
- Start with breadboard version, then move to perfboard/PCB for permanent build

