# Pinout and Wiring Diagram

Complete pin assignments and wiring instructions for the Arduino Macro Keyboard.

## Pin Assignment Table

| Arduino Pin | Function | Connection Details | LED Pin (optional) | LED Behavior |
|-------------|----------|-------------------|-------------------|--------------|
| 2 | Volume Down button | Button → GND | 14 (A0) | Lights while pressed |
| 3 | Volume Up button | Button → GND | 15 (A1) | Lights while pressed |
| 4 | Mute | Button → GND | 16 (A2) | Toggle red / off |
| 5 | Previous Track | Button → GND | 18 | Flash on press |
| 6 | Play/Pause | Button → GND | 19 | Flash on press |
| 7 | Next Track | Button → GND | 21 (SDA) | Flash on press |
| 8 | Open Spotify | Button → GND | 9 | Lights while pressed |
| 9 | Open AMD Adrenaline | Button → GND | 10 | Lights while pressed |
| 10 | Open Steam | Button → GND | 8 | Lights while pressed |
| 0 & 1 | Rotary Encoder CLK & DT | Encoder pins + 5V & GND | – | – |
| 14 (A0) | Encoder push (mute) | Encoder SW → GND | Same as mute LED | – |

## Wiring Instructions

### Buttons
All buttons use **internal pull-ups**, so wiring is extremely simple:
- One side of button → Arduino digital pin
- Other side of button → GND
- **No external resistors needed!**

### LEDs
Each LED requires a current-limiting resistor:
- **Long leg (anode)** → Arduino pin → **220Ω resistor** → **Short leg (cathode)** → GND
- Resistor can be on either side of LED (before or after)

### Rotary Encoder
If using a rotary encoder instead of separate volume buttons:
- **CLK** → Pin 0 (interrupt-capable)
- **DT** → Pin 1 (interrupt-capable)
- **SW** → Pin 14 (A0) for push-to-mute
- **+** → 5V
- **GND** → GND

**Note:** If using encoder, pins 2 & 3 are freed up for additional buttons.

## Breadboard Layout

```
Arduino Pro Micro          Breadboard
─────────────────          ─────────
    5V ────────────┬─────── 5V rail
   GND ────────────┼─────── GND rail
                   
   Pin 2 ──────────┼─────── Button 1 ──── GND
   Pin 3 ──────────┼─────── Button 2 ──── GND
   Pin 4 ──────────┼─────── Button 3 ──── GND
   Pin 5 ──────────┼─────── Button 4 ──── GND
   Pin 6 ──────────┼─────── Button 5 ──── GND
   Pin 7 ──────────┼─────── Button 6 ──── GND
   Pin 8 ──────────┼─────── Button 7 ──── GND
   Pin 9 ──────────┼─────── Button 8 ──── GND
   Pin 10 ─────────┼─────── Button 9 ──── GND
   
   Pin 18 ────[220Ω]─── LED 1 ──── GND
   Pin 19 ────[220Ω]─── LED 2 ──── GND
   Pin 21 ────[220Ω]─── LED 3 ──── GND
```

## Pro Micro Pin Reference

The Arduino Pro Micro has the following pins available:

**Digital Pins:**
- 0, 1 (RX, TX) - **Interrupt-capable** - Use for rotary encoder
- 2–10 - Standard digital I/O
- 14–21 (A0–A7) - Analog pins, can be used as digital I/O
- 18 (A0), 19 (A1), 20 (A2), 21 (A3) - Commonly used for LEDs

**Important Notes:**
- Pins 0 & 1 are used for USB serial communication, but can be used for I/O when not programming
- All pins support `INPUT_PULLUP` mode
- Pins 0, 1, 2, 3, 7 support hardware interrupts (useful for rotary encoder)

## Example: 9-Button Layout with Rotary Encoder

If using a rotary encoder for volume (recommended), you can free up pins 2 & 3:

| Pin | Function |
|-----|----------|
| 0 | Encoder CLK |
| 1 | Encoder DT |
| 4 | Mute (or encoder push) |
| 5 | Previous Track |
| 6 | Play/Pause |
| 7 | Next Track |
| 8 | Spotify |
| 9 | AMD Adrenaline |
| 10 | Steam |
| 2, 3 | Available for additional buttons |

## Upgraded Pinout (with WS2812B + Nextion)

After implementing upgrades (see [docs/upgrade_roadmap.md](../docs/upgrade_roadmap.md)):

| Arduino Pin | Function | Connection | Notes |
|-------------|----------|------------|-------|
| 0 (RX) | Nextion TX | Nextion display serial | Serial1 |
| 1 (TX) | Nextion RX | Nextion display serial | Serial1 |
| 2 | Encoder CLK | Rotary encoder | Interrupt-capable |
| 3 | Encoder DT | Rotary encoder | Interrupt-capable |
| 4 | Encoder SW | Rotary encoder button | Mute toggle |
| 5-8 | Optional buttons | Physical buttons (if keeping) | Can be removed if using Nextion |
| 9 | WS2812B Data | LED strip data line | Via 330Ω resistor |
| 10-21 | Spare | Future expansion | 12 pins available |

**Power Connections:**
- 5V → Nextion VCC, WS2812B 5V, Encoder VCC
- GND → Common ground for all components
- RAW → Not used (optional external power input)

**Notes:**
- Nextion uses Serial1 (pins 0/1), USB serial (`Serial`) remains available for debugging
- WS2812B supports up to ~30 LEDs on Pro Micro 5V (500mA limit)
- Still have 12+ pins free for expansion (buttons, sensors, etc.)

## Troubleshooting

### Basic Hardware

**Button not working:**
- Check that button is connected to pin and GND (not 5V)
- Verify pin mode is set to `INPUT_PULLUP` in code
- Test with multimeter: should read LOW when pressed

**LED not lighting:**
- Check polarity (long leg = anode, short leg = cathode)
- Verify 220Ω resistor is in series
- Test LED directly with 5V and resistor to verify it works

**Rotary encoder not smooth:**
- Ensure CLK and DT are on interrupt-capable pins (0 & 1)
- Use interrupt-based reading or Encoder library
- Add proper debouncing in code

### Upgrade-Specific

**WS2812B LEDs not working:**
- Verify data pin connection (pin 9 in examples)
- Check FastLED color order: try GRB, RGB, or BRG
- Test with simple example: `leds[0] = CRGB::Red; FastLED.show();`
- Ensure 5V and GND are connected to strip
- Add 330Ω resistor on data line if experiencing glitches
- If >30 LEDs, use external 5V power supply

**Nextion display blank:**
- Check serial connection: TX → RX, RX → TX (crossed)
- Verify baud rate matches (9600 default)
- Ensure display has valid .tft file uploaded via microSD
- Test with simple command: `Serial1.print("page 0");` + 3× 0xFF

**Real-time feedback not working:**
- Verify Python script is running (check Task Manager / Activity Monitor)
- Check serial port in Python script matches Arduino port
- Test serial connection: Arduino should print received characters
- Ensure companion script has valid Spotify API credentials
- Check USB cable supports data (some are charge-only)

