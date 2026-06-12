# bochka_system
The "bochka" (or the "бочка") is a barrel in Russian.
The Arduino board interacts with the XKC-Y25-V sensor and turns on any type of pump via the SSR relay. It was originally designed for a 50-liter barrel.

## How it works

The system monitors the water level using a non-contact capacitive sensor (XKC-Y25-V). When the water level drops below the sensor, the system waits **30 minutes** before turning the pump on. When water is detected again, the system waits **15 seconds** before turning the pump off.

This delay logic prevents the pump from short-cycling and protects it from damage caused by frequent switching.

## Hardware requirements

- Arduino board (Uno, Nano, Mega, etc.)
- XKC-Y25-V non-contact liquid level sensor
- SSR relay (or any compatible relay module)
- Pump (12V/220V depending on your setup)
- 50-liter barrel (or any water container)

## Wiring

| Component | Arduino Pin |
|-----------|-------------|
| XKC-Y25-V signal | Digital Pin 2 |
| SSR relay control pin | Digital Pin 3 |
| XKC-Y25-V VCC | 5V |
| XKC-Y25-V GND | GND |
| Relay VCC | 5V |
| Relay GND | GND |

> **Note:** The internal pull-up resistor of the Arduino is enabled in the software (digitalWrite(SENSOR_PIN, HIGH)), so no external resistor is required between the sensor and the Arduino.

## Example of Installation

The system is in a small case
![The system is in a small case](bochka/photos/1781182154777.jpg)

Connecting the XKC-Y25-V sensor 
![Connecting the XKC-Y25-V sensor ](bochka/photos/1781182154786.jpg)

The system is on a barrel
![The system is on a barrel](bochka/photos/1000013495.jpg)



## Sensor logic

- **LOW signal** = Water detected
- **HIGH signal** = No water detected

## Timing parameters (can be modified in code)

| Parameter | Value | Description |
|-----------|-------|-------------|
| `DELAY_BEFORE_ON` | 30 minutes | Pump turns on only after water has been absent for 30 minutes |
| `DELAY_BEFORE_OFF` | 15 seconds | Pump turns off after water has been present for 15 seconds |

## Serial monitoring

The system outputs its status to the Serial Monitor at **9600 baud**. You will see messages like:
- `Water level: NOT DETECTED (HIGH signal)`
- `Water level: DETECTED (LOW signal)`
- `Relay TURNED ON - 30 minutes passed without water`
- `Relay TURNED OFF - Water level remained high for 15 seconds`

## Customization

You can easily adjust the timing delays by changing the constants at the top of the sketch:
```cpp
const unsigned long DELAY_BEFORE_ON = 30UL * 60UL * 1000UL;  // Change 30 to any minutes
const unsigned long DELAY_BEFORE_OFF = 15UL * 1000UL;        // Change 15 to any seconds
```

## License

Feel free to use, modify, and distribute this code for personal or commercial projects.

---
