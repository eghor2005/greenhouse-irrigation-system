Here's a detailed README for your Arduino-based automatic watering system project:


# AquaFlora - Smart Automatic Watering System

An Arduino-based automatic plant watering system with a graphical TFT display, potentiometer-controlled timing, and dual SSR relay outputs for water pumps.

![The finished product](greenhouse-irrigation-system/aquaflora/photos/1000013501.jpg)
## 📋 Overview

AquaFlora is an intelligent watering system that allows you to precisely control watering duration using a potentiometer and trigger watering cycles with a single button press. The system features a colorful TFT display showing real-time information, watering progress, and system status.

## 🎥 Features

- **Interactive TFT Display** (ST7735 based)
  - Boot animation with system status
  - Real-time watering interval display
  - Visual progress bar for potentiometer feedback
  - Color-coded status messages (success/error states)

- **Precise Watering Control**
  - Potentiometer-controlled timing (1-600 seconds)
  - 50-step increments for smooth adjustment
  - Visual feedback via progress bar

- **Dual Relay Outputs**
  - Control two water pumps simultaneously
  - LED indicators (if connected) for visual feedback
  - Automatic shutoff after watering completes

- **User Interface**
  - Debounced button input to prevent false triggers
  - Clear on-screen instructions
  - Progress tracking during watering cycles
  - Completion confirmation screen

## 🔧 Hardware Requirements

### Components
- Arduino board (Uno/Nano/Mega recommended)
- ST7735-based TFT display (128x160 pixels)
- 10kΩ potentiometer
- Push button (Normally Open)
- 2x SSR Relay modules
- 2x Water pumps
- Connecting wires
- Power supply (appropriate for your pumps/valves)

### Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| TFT CS     | 10          |
| TFT RST    | 9           |
| TFT DC     | 8           |
| Relay 1    | 5           |
| Relay 2    | 6           |
| Button     | 2 (INPUT_PULLUP) |
| Potentiometer | A0       |

### Required Libraries

Install these libraries through Arduino Library Manager:

```cpp
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
```

## 📦 Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/aquaflora-watering-system.git
   cd aquaflora-watering-system
   ```

2. **Install required libraries**
   - Open Arduino IDE
   - Go to Sketch → Include Library → Manage Libraries
   - Search and install:
     - "Adafruit GFX Library"
     - "Adafruit ST7735 and ST7789 Library"

3. **Connect hardware** according to the pin configuration table above

4. **Upload the code**
   - Open the `.ino` file in Arduino IDE
   - Select your board and port
   - Click Upload

## 🚀 Usage Guide

### Setting Watering Duration
1. Turn the potentiometer to adjust watering time
2. The display shows:
   - Current selected seconds (1-600)
   - A visual progress bar representing the duration
3. The value updates in real-time as you turn the knob

### Starting a Watering Cycle
1. Press the button once to start watering
2. The system will:
   - Display a "WATERING START" screen
   - Activate both relays simultaneously
   - Count down in real-time
   - Show a progress bar and timer

### During Watering
- The display shows remaining time in seconds
- A progress bar indicates cycle completion
- Both relays remain active throughout the set duration

### After Completion
- Relays automatically deactivate
- "COMPLETED!" screen appears for 2 seconds
- System returns to main screen for next cycle

## 📊 Code Structure

### Key Functions

| Function | Description |
|----------|-------------|
| `drawLoadingScreen()` | Boot animation with progress indicator |
| `drawMainScreen()` | Main user interface layout |
| `drawPotentiometerIcon()` | Visual feedback for selected duration |
| `updateDisplay()` | Real-time UI updates |
| `startWatering()` | Main watering routine with progress tracking |

### Technical Details

- **Debouncing**: 50ms delay to prevent multiple button triggers
- **Potentiometer Smoothing**: Values rounded to nearest 50 for stable display
- **Display Refresh**: Only updates when values change (minimizes flicker)
- **Non-blocking Design**: Main loop remains responsive during idle states
- **Safety Features**: Automatic relay shutoff after completion

## 🔧 Customization

### Adjusting Time Range
Modify these lines in the code:
```cpp
// For different max time (currently 600 seconds = 10 minutes)
selectedSeconds = map(potValue, 0, 1023, 1, YOUR_MAX_SECONDS);
```

### Changing Colors
Modify the color definitions at the top:
```cpp
#define BG_COLOR     ST77XX_BLACK
#define TEXT_COLOR   ST77XX_WHITE
#define ACCENT_COLOR ST77XX_CYAN
// Available colors: ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE, etc.
```

### Single Relay Operation
If you only need one pump:
```cpp
// Comment out or remove second relay operations
// digitalWrite(RELAY2, HIGH);
// digitalWrite(RELAY2, LOW);
```

## ⚠️ Important Notes

1. **Power Considerations**
   - Common Relays (NOT SSR) require separate power for pumps/valves
   - Do not power pumps directly from Arduino
   - Use appropriate flyback diodes for inductive loads

2. **Water Safety**
   - Keep electronics away from water sources
   - Use waterproof enclosures for outdoor use
   - Consider adding manual override switches

3. **Display Compatibility**
   - Code configured for INITR_GREENTAB (1.8" ST7735)
   - For other variants, change initialization line:
     ```cpp
     tft.initR(INITR_BLACKTAB);  // or INITR_REDTAB
     ```


## 📝 License

This project is open-source and available under the MIT License.
