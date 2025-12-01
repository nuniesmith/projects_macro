# Examples Directory

This directory contains working code examples for upgrading your stream deck. Each example builds on the basic project to add new features.

## 📁 Files

### `led_upgrade_example.ino`
**Upgrade 1: WS2812B RGB LEDs**

Adds individually addressable RGB LEDs for color-coded visual feedback.

**Features:**
- FastLED library integration
- Color-coded buttons (blue for media, green for Spotify, etc.)
- White flash on button press
- Optional breathing effect on idle LEDs
- Power-efficient (supports up to 30 LEDs on Pro Micro)

**Requirements:**
- WS2812B LED strip (12-30 LEDs)
- 330Ω resistor
- FastLED library (install via Arduino Library Manager)

**Wiring:**
```
Pin 10 → 330Ω resistor → WS2812B Data In
5V → LED Strip 5V
GND → LED Strip GND
```

---

### `realtime_companion.py`
**Upgrade 2: Real-Time Status Monitoring**

Python companion script that monitors PC state and sends updates to Arduino via serial.

**Features:**
- Spotify playback state (playing/paused/stopped)
- System volume level (0-100%)
- Mute state detection
- Auto-reconnect on errors
- Cross-platform serial detection

**Requirements:**
```bash
pip install spotipy pyserial pycaw-python pywin32
```

**Configuration:**
1. Get Spotify API credentials: https://developer.spotify.com/dashboard
2. Update `SERIAL_PORT` to match your Arduino port
3. Update `SPOTIFY_CLIENT_ID` and `SPOTIFY_CLIENT_SECRET`

**Usage:**
```bash
python realtime_companion.py
```

**Auto-start on Windows:**
1. Create shortcut to script
2. Press `Win+R`, type: `shell:startup`
3. Move shortcut to Startup folder

---

### `arduino_with_feedback.ino`
**Complete Example: Arduino + LEDs + Real-Time Feedback**

Combines WS2812B LEDs with serial communication for real-time status updates from the companion script.

**Features:**
- All features from `led_upgrade_example.ino`
- Serial protocol for receiving status updates
- Spotify state indicator (green=playing, orange=paused)
- Volume bar graph on LEDs 7-11
- Mute indicator (red LED)
- Button press handling with visual feedback

**Requirements:**
- Same as `led_upgrade_example.ino`
- Must run `realtime_companion.py` on PC

**Serial Protocol:**
| Command | Meaning | Arduino Response |
|---------|---------|------------------|
| `P` | Spotify playing | LED green |
| `p` | Spotify paused | LED orange |
| `S` | Spotify stopped | LED dim green |
| `M` | Muted | LED red |
| `m` | Unmuted | LED off |
| 0-100 (byte) | Volume level | Update volume bar |

**Usage:**
1. Upload sketch to Arduino
2. Note the COM port (Tools → Port)
3. Update `SERIAL_PORT` in `realtime_companion.py`
4. Run Python script
5. LEDs will show real-time status!

---

## 🚀 Getting Started

### Quick Start (LED Upgrade Only)
1. Install FastLED library (Sketch → Include Library → Manage Libraries)
2. Upload `led_upgrade_example.ino` to Arduino
3. Connect WS2812B strip to pin 10
4. Enjoy color-coded buttons!

### Full Setup (LEDs + Real-Time Feedback)
1. Upload `arduino_with_feedback.ino` to Arduino
2. Install Python dependencies:
   ```bash
   pip install spotipy pyserial pycaw-python pywin32
   ```
3. Configure `realtime_companion.py` (Spotify API + serial port)
4. Run Python script:
   ```bash
   python realtime_companion.py
   ```
5. Watch your LEDs react to Spotify and volume changes!

---

## 🎨 Customization Ideas

### Color Schemes

**Dark Mode:**
```cpp
leds[LED_PREV] = CRGB(0, 0, 50);   // Dim blue
leds[LED_SPOTIFY] = CRGB(0, 50, 0); // Dim green
```

**RGB Rainbow:**
```cpp
for(int i = 0; i < NUM_LEDS; i++) {
  leds[i] = CHSV(i * 255/NUM_LEDS, 255, brightness);
}
```

**Brand Colors:**
- Spotify: `CRGB(29, 185, 84)` - #1DB954
- Discord: `CRGB(88, 101, 242)` - #5865F2
- Twitch: `CRGB(145, 70, 255)` - #9146FF
- YouTube: `CRGB(255, 0, 0)` - #FF0000

### Additional Status Monitors

Add to `realtime_companion.py`:

**Discord mute state:**
```python
# Requires discord.py library
@client.event
async def on_voice_state_update(member, before, after):
    if member == client.user:
        if after.self_mute:
            ser.write(b'D')  # Discord muted
```

**OBS streaming state:**
```python
# Requires obs-websocket-py
obs = obsws("localhost", 4455, "password")
status = obs.call(requests.GetStreamStatus())
if status.getStreaming():
    ser.write(b'O')  # OBS streaming
```

**CPU/RAM monitoring:**
```python
import psutil
cpu = psutil.cpu_percent()
ser.write(bytes([int(cpu)]))  # Send CPU usage
```

---

## 🐛 Troubleshooting

### WS2812B LEDs not working
- **Wrong color order:** Try `GRB`, `RGB`, or `BRG` in FastLED setup
- **No power:** Verify 5V and GND connections
- **Data line noise:** Add 330Ω resistor between pin and data in
- **Dim LEDs:** Increase brightness: `FastLED.setBrightness(150)`

### Python script errors
- **Serial port not found:** Check Device Manager (Windows) or `ls /dev/tty*` (Linux/Mac)
- **Module not found:** Run `pip install <module>` for missing libraries
- **Spotify auth fails:** Verify client ID/secret, check redirect URI
- **Permission denied (Linux):** Add user to `dialout` group: `sudo usermod -a -G dialout $USER`

### Arduino not receiving commands
- **Wrong baud rate:** Ensure both sides use 115200
- **USB cable:** Some cables are charge-only, use data-capable cable
- **Serial conflict:** Close Arduino Serial Monitor before running Python script
- **Buffer overflow:** Add delays between serial writes in Python

### Real-time status laggy
- **Increase update interval:** Change `UPDATE_INTERVAL = 1.0` to `0.5` in Python
- **Reduce serial traffic:** Only send on state change (already implemented)
- **Check CPU usage:** Close other apps if system is slow

---

## 📚 Next Steps

After mastering these examples, check out:

1. **[docs/upgrade_roadmap.md](../docs/upgrade_roadmap.md)** - Full upgrade guide
2. **[docs/upgrade_quick_reference.md](../docs/upgrade_quick_reference.md)** - Quick lookup
3. **Nextion Display** - Add touchscreen GUI (Upgrade 3)
4. **Custom PCB** - Design professional build (Upgrade 4)
5. **3D-Printed Case** - Final enclosure (Upgrade 5)

---

## 🤝 Contributing

Have improvements or new examples? Consider:
- Adding more status monitors (Discord, OBS, system stats)
- Creating effects libraries (rainbow cycle, fire effect, etc.)
- Writing guides for other platforms (macOS, Linux audio control)
- Designing alternative layouts (vertical, circular, split)

---

## 📄 License

These examples are part of the Arduino Stream Deck project and are open source.

**Libraries Used:**
- FastLED - MIT License
- Spotipy - MIT License
- pycaw - MIT License
- Arduino Keyboard Library - LGPL

Feel free to modify and share!
