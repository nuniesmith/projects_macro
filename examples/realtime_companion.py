#!/usr/bin/env python3
"""
Stream Deck Real-Time Companion Script

Monitors PC state (Spotify, volume, mute, etc.) and sends updates to Arduino
via serial. Enables real-time visual feedback on LEDs and displays.

Requirements:
    pip install spotipy pyserial pycaw-python pywin32

Setup:
    1. Get Spotify API credentials: https://developer.spotify.com/dashboard
    2. Update SERIAL_PORT to match your Arduino (Windows: COM3, Linux: /dev/ttyACM0)
    3. Update Spotify credentials below
    4. Run script: python realtime_companion.py

Auto-start on Windows:
    1. Create shortcut to this script
    2. Press Win+R, type: shell:startup
    3. Move shortcut to Startup folder
"""

import serial
import time
import sys
import platform

# Spotify support
try:
    import spotipy
    from spotipy.oauth2 import SpotifyOAuth
    SPOTIFY_AVAILABLE = True
except ImportError:
    print("Warning: spotipy not installed. Spotify features disabled.")
    print("Install with: pip install spotipy")
    SPOTIFY_AVAILABLE = False

# Windows audio support
if platform.system() == 'Windows':
    try:
        from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
        from ctypes import cast, POINTER
        from comtypes import CLSCTX_ALL
        AUDIO_AVAILABLE = True
    except ImportError:
        print("Warning: pycaw not installed. Volume monitoring disabled.")
        print("Install with: pip install pycaw-python pywin32")
        AUDIO_AVAILABLE = False
else:
    print(f"Audio monitoring not implemented for {platform.system()}")
    AUDIO_AVAILABLE = False

# =============================================================================
# CONFIGURATION
# =============================================================================

# Serial port configuration
SERIAL_PORT = 'COM3'  # Windows: COM3, Linux: /dev/ttyACM0, Mac: /dev/cu.usbmodem
BAUD_RATE = 115200
UPDATE_INTERVAL = 1.0  # seconds between updates

# Spotify API credentials (get from: https://developer.spotify.com/dashboard)
SPOTIFY_CLIENT_ID = "YOUR_CLIENT_ID_HERE"
SPOTIFY_CLIENT_SECRET = "YOUR_CLIENT_SECRET_HERE"
SPOTIFY_REDIRECT_URI = "http://localhost:8888/callback"

# =============================================================================
# SERIAL PROTOCOL
# =============================================================================
# Commands sent to Arduino (single characters):
#   'P' = Spotify playing
#   'p' = Spotify paused
#   'S' = Spotify stopped
#   'M' = Muted
#   'm' = Unmuted
#   0-100 (byte) = Volume level
# =============================================================================

class StreamDeckCompanion:
    def __init__(self):
        # Initialize serial connection
        try:
            self.ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
            time.sleep(2)  # Wait for Arduino reset after serial connection
            print(f"✓ Connected to Arduino on {SERIAL_PORT}")
        except serial.SerialException as e:
            print(f"✗ Failed to connect to {SERIAL_PORT}: {e}")
            print("\nAvailable ports:")
            self.list_serial_ports()
            sys.exit(1)
        
        # Initialize Spotify
        self.spotify = None
        if SPOTIFY_AVAILABLE:
            try:
                if SPOTIFY_CLIENT_ID == "YOUR_CLIENT_ID_HERE":
                    print("⚠ Spotify credentials not configured. Spotify features disabled.")
                    print("  Get credentials from: https://developer.spotify.com/dashboard")
                else:
                    auth_manager = SpotifyOAuth(
                        client_id=SPOTIFY_CLIENT_ID,
                        client_secret=SPOTIFY_CLIENT_SECRET,
                        redirect_uri=SPOTIFY_REDIRECT_URI,
                        scope="user-read-playback-state"
                    )
                    self.spotify = spotipy.Spotify(auth_manager=auth_manager)
                    print("✓ Spotify API initialized")
            except Exception as e:
                print(f"⚠ Spotify initialization failed: {e}")
        
        # Initialize Windows audio
        self.volume_interface = None
        if AUDIO_AVAILABLE:
            try:
                devices = AudioUtilities.GetSpeakers()
                interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
                self.volume_interface = cast(interface, POINTER(IAudioEndpointVolume))
                print("✓ Windows audio interface initialized")
            except Exception as e:
                print(f"⚠ Audio initialization failed: {e}")
    
    def get_spotify_state(self):
        """Return Spotify playback state character"""
        if not self.spotify:
            return None
        
        try:
            current = self.spotify.current_playback()
            if current and current['is_playing']:
                return 'P'  # Playing
            elif current:
                return 'p'  # Paused
            else:
                return 'S'  # Stopped / No active device
        except Exception as e:
            # Don't spam errors during normal operation
            return None
    
    def get_volume_state(self):
        """Return (volume_level, is_muted) tuple"""
        if not self.volume_interface:
            return None, None
        
        try:
            vol_level = self.volume_interface.GetMasterVolumeLevelScalar()
            is_muted = self.volume_interface.GetMute()
            return int(vol_level * 100), is_muted
        except Exception as e:
            return None, None
    
    def send_update(self, command):
        """Send single character or byte to Arduino"""
        if isinstance(command, str):
            self.ser.write(command.encode())
        elif isinstance(command, int):
            self.ser.write(bytes([command]))
    
    def run(self):
        """Main monitoring loop"""
        print("\n" + "="*50)
        print("Stream Deck Companion Running")
        print("="*50)
        print("Press Ctrl+C to stop\n")
        
        last_spotify_state = None
        last_volume = None
        last_mute = None
        
        try:
            while True:
                # Get current states
                spotify_state = self.get_spotify_state()
                volume_level, is_muted = self.get_volume_state()
                
                # Only send updates when state changes (reduces serial traffic)
                if spotify_state and spotify_state != last_spotify_state:
                    self.send_update(spotify_state)
                    state_text = {
                        'P': 'Playing',
                        'p': 'Paused',
                        'S': 'Stopped'
                    }.get(spotify_state, 'Unknown')
                    print(f"Spotify: {state_text}")
                    last_spotify_state = spotify_state
                
                if volume_level is not None and volume_level != last_volume:
                    self.send_update(volume_level)
                    print(f"Volume: {volume_level}%")
                    last_volume = volume_level
                
                if is_muted is not None and is_muted != last_mute:
                    self.send_update('M' if is_muted else 'm')
                    print(f"Mute: {'ON' if is_muted else 'OFF'}")
                    last_mute = is_muted
                
                time.sleep(UPDATE_INTERVAL)
                
        except KeyboardInterrupt:
            print("\n\nShutting down gracefully...")
            self.ser.close()
            print("✓ Serial connection closed")
    
    @staticmethod
    def list_serial_ports():
        """List available serial ports"""
        import serial.tools.list_ports
        ports = serial.tools.list_ports.comports()
        if ports:
            for port in ports:
                print(f"  - {port.device}: {port.description}")
        else:
            print("  No serial ports found")

def main():
    print("""
╔════════════════════════════════════════════════════════════╗
║        Stream Deck Real-Time Companion v1.0               ║
║        Monitors PC state and updates Arduino              ║
╚════════════════════════════════════════════════════════════╝
    """)
    
    companion = StreamDeckCompanion()
    companion.run()

if __name__ == "__main__":
    main()
