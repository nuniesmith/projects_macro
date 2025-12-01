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

- **[Arduino Macro Keyboard](https://www.instructables.com/Arduino-Stream-Deck/)** - Instructables
  - Complete build guide with 3D printing files
  - Multiple button layouts

### Volume Control Projects
- **[PC USB Media Volume Controller Based on Arduino](https://www.instructables.com/PC-USB-Media-Volume-Controller-based-on-Arduino/)** - Instructables
  - Best volume knob + RGB feedback example
  - Edge-lit acrylic with volume-level bargraph LEDs
  - Very close to commercial products

## Advanced Projects

### Touchscreen Versions
- **[DIY Stream Deck with Arduino Nextion](https://www.hackster.io/ElectronicCNCLAB/diy-stream-deck-with-arduino-nextion-96c64f)** - Hackster.io (March 2025)
  - **Most popular 2025 build** - complete KiCad files + 3D models
  - Nextion 3.5" display integration with GUI examples
  - Python companion script in comments for real-time feedback
  - Full upgrade path from basic to professional

- **[DIY Stream Deck Customize Your Buttons](https://www.instructables.com/DIY-Stream-Deck-With-Arduino-Nextion-Customize-You/)** - Instructables
  - Excellent Nextion Editor walkthrough
  - Icon creation and upload tutorial
  - Button animation examples

### YouTube Tutorials
- **"DIY Stream Deck with Arduino!"** (March 2025)
  - Nextion/OLED screen integration
  - Real-time feedback implementation
  - Underlying HID code and wiring identical to simple versions

## Technical Resources

### Arduino Pro Micro
- [SparkFun Pro Micro Hookup Guide](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide)
- [Arduino Leonardo Pin Reference](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/) (Pro Micro uses same core)

### USB HID
- [Arduino Keyboard Library Reference](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/)
- [USB HID Usage Tables](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) - Official HID codes

### Upgrade-Specific Resources

#### WS2812B RGB LEDs
- [FastLED Library Documentation](https://github.com/FastLED/FastLED/wiki/Overview) - Best LED library
- [Random Nerd Tutorials: WS2812B Guide](https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/)
- [Adafruit NeoPixel Überguide](https://learn.adafruit.com/adafruit-neopixel-uberguide)

#### Real-Time Feedback
- [Spotipy Documentation](https://spotipy.readthedocs.io/) - Spotify API wrapper
- [pycaw GitHub](https://github.com/AndreCAndersen/pycaw) - Windows audio control
- [pySerial Documentation](https://pyserial.readthedocs.io/) - Serial communication

#### Nextion Display
- [Nextion Instruction Set](https://nextion.tech/instruction-set/) - Command reference
- [Nextion Editor Download](https://nextion.tech/nextion-editor/) - Free GUI designer
- [Nextion Arduino Library](https://github.com/itead/ITEADLIB_Arduino_Nextion)

#### Custom PCB Design
- [KiCad 8 Download](https://www.kicad.org/download/) - Free PCB design software
- [Getting to Blinky Tutorial](https://www.youtube.com/watch?v=BVhWh3AsXQs) - Phil's Lab (best KiCad intro)
- [ai03 Keyboard PCB Guide](https://wiki.ai03.com/books/pcb-design/chapter/pcb-guide-part-1---preparations) - Industry standard
- [KiCad Libraries for MX switches](https://github.com/ai03-2725/MX_Alps_Hybrid)
- [JLCPCB](https://jlcpcb.com/) - PCB manufacturing ($12 for 5 boards)

#### 3D Printing
- [Thingiverse Stream Deck Cases](https://www.thingiverse.com/search?q=stream+deck&type=things&sort=popular)
- [Printables Macropad Cases](https://www.printables.com/search/models?q=macropad)
- [Super Make Something Cases](https://www.thingiverse.com/thing:4650060) - Most popular
- [Swillkb Plate Builder](http://builder.swillkb.com/) - Parametric case generator
- [3D Printing Guide for Keyboards](https://all3dp.com/2/diy-stream-deck-3d-print/)

### Open-Source Project Templates

#### KiCad PCB Files
- **Hackster Nextion Stream Deck** (2025) - Complete 3×4 layout with hotswap
- **BDN9 by keeb.io** - Well-documented 3×3 macropad
- **Corne-ish Macropad** - Highly customizable template

Search GitHub for: "arduino stream deck", "macropad kicad pro micro", "hotswap macropad"

#### Arduino Code Examples
- [witnessmenow/spotify-api-arduino](https://github.com/witnessmenow/spotify-api-arduino) - Spotify integration
- [FastLED Examples](https://github.com/FastLED/FastLED/tree/master/examples) - LED effects library

### Community Resources

#### Forums & Discord
- r/MechanicalKeyboards - Active DIY community
- r/Arduino - Hardware troubleshooting
- 40percent.club Discord - Macropad enthusiasts
- MechKeys Discord - PCB design help

#### YouTube Channels
- **Super Make Something** - Original DIY stream deck builds
- **Great Scott** - Arduino project tutorials
- **Phil's Lab** - PCB design tutorials
- **Teaching Tech** - 3D printing guides

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

