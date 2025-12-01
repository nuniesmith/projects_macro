# Arduino Macro Keyboard

A DIY USB HID macro keyboard and media controller built with Arduino Pro Micro. Control media playback, system volume, and launch applications with physical buttons and a rotary encoder.

## Features

- **Media Controls**: Play/Pause, Next Track, Previous Track
- **Volume Control**: Rotary encoder for smooth volume adjustment + mute toggle
- **Application Launcher**: Quick-launch buttons for Spotify, AMD Adrenaline, Steam, and more
- **Visual Feedback**: LED indicators for button presses and status
- **Native USB HID**: Works on Windows, macOS, and Linux without additional software

## Hardware Requirements

- 1× Arduino Pro Micro (5V/16MHz) or compatible clone
- 9–12× Tactile buttons (6×6mm or 12×12mm)
- 1× Rotary encoder with push switch (KY-040 or EC11)
- 9–12× LEDs (3mm or 5mm) + 220Ω resistors
- Breadboard + jumper wires
- Optional: Cherry MX/Gateron switches + keycaps for final build

See [hardware/BOM.md](hardware/BOM.md) for detailed component list and [hardware/pinout.md](hardware/pinout.md) for wiring diagram.

## Quick Start

1. **Hardware Setup**
   - Wire buttons from digital pins to GND (using internal pull-ups)
   - Connect LEDs through 220Ω resistors to GND
   - Connect rotary encoder CLK/DT to interrupt-capable pins (0 & 1)
   - See [hardware/pinout.md](hardware/pinout.md) for complete wiring

2. **Software Setup**
   - Install [Arduino IDE](https://www.arduino.cc/en/software)
   - Select board: **Tools → Board → Arduino Leonardo** (Pro Micro uses same core)
   - Select port: **Tools → Port → [your Pro Micro port]**
   - Open `src/stream_deck.ino`
   - Upload to board

3. **Customization**
   - Edit button pins in `src/stream_deck.ino`
   - Modify application shortcuts to match your taskbar layout
   - Adjust LED pins and behavior as needed

## Project Structure

```
stream/
├── src/                         # Arduino source code
│   └── stream_deck.ino         # Main sketch
├── examples/                    # Upgrade examples
│   ├── led_upgrade_example.ino         # WS2812B RGB LEDs
│   ├── realtime_companion.py           # PC status monitor
│   └── arduino_with_feedback.ino       # Complete feedback example
├── hardware/                    # Hardware documentation
│   ├── BOM.md                  # Bill of Materials
│   └── pinout.md               # Pin assignments and wiring
├── docs/                        # Additional documentation
│   ├── references.md           # Citations and resources
│   └── upgrade_roadmap.md      # Comprehensive upgrade guide
└── README.md                   # This file
```

## How It Works

The Arduino Pro Micro's ATMega32U4 chip natively supports USB HID, allowing it to act as a keyboard and media controller. The code uses the standard `Keyboard` library to send:

- **Media keys**: Raw HID codes (0xE9, 0xEA, etc.) for volume and playback
- **Keyboard shortcuts**: Win+number for taskbar apps, Alt+R for AMD overlay, etc.

All buttons use internal pull-ups (INPUT_PULLUP), so wiring is simple: button between pin and GND. LEDs provide visual feedback on button presses.

## Customization Guide

### Adding New Buttons

1. Define pin constant: `const int pinNewButton = 11;`
2. Set pin mode in `setup()`: `pinMode(pinNewButton, INPUT_PULLUP);`
3. Add button logic in `loop()`: `if (digitalRead(pinNewButton) == LOW) { ... }`

### Changing Application Shortcuts

- **Taskbar apps**: Pin to taskbar, use `Win+1`, `Win+2`, etc.
- **Custom shortcuts**: Create desktop shortcuts with `Ctrl+Alt+letter` hotkeys
- **AMD Adrenaline**: Default is `Alt+R` (overlay) or `Ctrl+Shift+A` (settings)

### Rotary Encoder

The encoder provides smooth volume control. CLK and DT pins should connect to interrupt-capable pins (0 & 1 on Pro Micro). The push switch can be used for mute toggle.

## Future Enhancements

This project is designed to be upgraded incrementally. See **[docs/upgrade_roadmap.md](docs/upgrade_roadmap.md)** for comprehensive upgrade documentation including:

- ✅ **WS2812B RGB LEDs** - Color-coded visual feedback (1 weekend, $5-15)
- ✅ **Real-time Status** - Spotify/volume/mute indicators via Python companion (1 weekend, free)
- ✅ **Nextion Display** - Touchscreen GUI with icons (2-3 days, $25-60)
- ✅ **Custom PCB** - Professional hotswap build with KiCad (1-2 weeks, $30-60)
- ✅ **3D-Printed Case** - Final enclosure (1 week, $10-30)

**Working Examples:** See `examples/` directory for upgrade code:
- `led_upgrade_example.ino` - WS2812B RGB LED integration
- `realtime_companion.py` - Python script for status monitoring
- `arduino_with_feedback.ino` - Complete example with real-time updates

**Total Upgrade Cost:** $40-$80 for professional stream deck comparable to $150 Elgato

## References

See [docs/references.md](docs/references.md) for tutorials, guides, and inspiration from the DIY community.

## License

This project is open source. Feel free to modify and share!
