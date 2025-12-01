# References and Resources

Tutorials, guides, and inspiration from the DIY community for building Arduino-based macro keyboards and stream decks.

## Primary Tutorials

### Basic Macro Keyboard
- **[DIY Arduino Macro Keyboard](https://www.instructables.com/DIY-Arduino-Macro-Keyboard-Increase-Your-Productiv/)** - Instructables
  - 12-button Cherry MX keyboard
  - Direct proof that Consumer.write() and Keyboard shortcuts work on Pro Micro
  - Excellent breadboard to final build progression

### Stream Deck Projects
- **[DIY Stream Deck (Mini Macro Keyboard)](https://www.partsnotincluded.com/diy-stream-deck-mini-macro-keyboard/)** - partsnotincluded.com
  - Excellent breadboard stage photographs
  - Pin-to-GND + internal pull-up technique
  - Software debouncing class example

- **[Arduino Stream Deck](https://www.instructables.com/Arduino-Stream-Deck/)** - Instructables
  - Complete build guide with 3D printing files
  - Multiple button layouts

### Volume Control Projects
- **[PC USB Media Volume Controller Based on Arduino](https://www.instructables.com/PC-USB-Media-Volume-Controller-based-on-Arduino/)** - Instructables
  - Best volume knob + RGB feedback example
  - Edge-lit acrylic with volume-level bargraph LEDs
  - Very close to commercial products

## Advanced Projects

### Touchscreen Versions
- **[DIY Stream Deck with Arduino Nextion](https://www.hackster.io/ElectronicCNCLAB/diy-stream-deck-with-arduino-nextion-96c64f)** - Hackster.io
  - Advanced touchscreen version
  - Nextion 3.5" display integration
  - Upgrade path for adding visual icons

### YouTube Tutorials
- **"DIY Stream Deck with Arduino!"** (March 2025)
  - Nextion/OLED screen integration
  - Underlying HID code and wiring identical to simple versions

## Technical Resources

### Arduino Pro Micro
- [SparkFun Pro Micro Hookup Guide](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide)
- [Arduino Leonardo Pin Reference](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/) (Pro Micro uses same core)

### USB HID
- [Arduino Keyboard Library Reference](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/)
- [USB HID Usage Tables](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) - Official HID codes

### Rotary Encoders
- [Encoder Library by Paul Stoffregen](https://www.pjrc.com/teensy/td_libs_Encoder.html)
- [KY-040 Rotary Encoder Tutorial](https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/)

## Community Resources

### Reddit
- r/arduino - General Arduino help
- r/MechanicalKeyboards - Switch and keycap recommendations
- r/streamdeck - Commercial Stream Deck discussions (good for feature ideas)

### Forums
- Arduino Forum - [USB HID Projects](https://forum.arduino.cc/c/using-arduino/other-arduino-products/arduino-leonardo-micro/15)
- Hackster.io - Search "Arduino macro keyboard" or "stream deck"

## Component Sources

### Recommended Suppliers
- **AliExpress** - Cheapest for bulk components (long shipping)
- **Amazon** - Fast shipping, good for prototyping
- **SparkFun** - Premium quality, excellent documentation
- **Adafruit** - Great tutorials and guides
- **DigiKey/Mouser** - Professional components for final builds

### Specific Components
- **Arduino Pro Micro Clones** - Search "Pro Micro 5V 16MHz" on AliExpress
- **KY-040 Encoder** - Available on Amazon, AliExpress, SparkFun
- **Cherry MX Switches** - Mechanical keyboard suppliers (NovelKeys, KBDfans, etc.)

## Best Practices (2025 Consensus)

Based on research across multiple 2024-2025 projects:

1. **Arduino Pro Micro (ATMega32U4)** is the standard for USB HID projects
2. **Direct pin-per-button** is fine up to ~18 buttons (no matrix needed)
3. **Media keys via raw HID codes** (0xE9, 0xEA, etc.) with stock Keyboard library is most reliable
4. **Rotary encoder for volume** is now standard (button-only feels cheap)
5. **App launching via Win+number** (taskbar) or Ctrl+Alt+letter (shortcuts) is fastest
6. **WS2812B LEDs** are common for final builds with RGB feedback

## Upgrade Path

1. **Start:** Breadboard with basic buttons and LEDs
2. **Upgrade 1:** Add rotary encoder for volume
3. **Upgrade 2:** Move to perfboard with Cherry MX switches
4. **Upgrade 3:** Add WS2812B RGB LEDs
5. **Upgrade 4:** Custom PCB design
6. **Upgrade 5:** Add OLED/Nextion display for icons
7. **Upgrade 6:** 3D-printed enclosure

Each step builds on the previous, and the HID code remains 99% the same throughout.

## License Notes

All referenced projects are for educational purposes. Check individual project licenses before commercial use.

