**GreenHouse Irrigation System** 🌱

Dual-mode Arduino plant watering system with TFT display.

**Manual mode** - Set duration (1-2048 sec) with potentiometer, press button to water.

**Auto mode** - No water for 30 min → pump ON. Water detected for 15 sec → pump OFF.

**Hardware:** ST7735 display, relay module, water sensor, potentiometer, button.

## The system in greenhouse
![The system is on a barrel](greenhouse-irrigation-system/photos/1.jpg)
![The system is on a barrel](greenhouse-irrigation-system/photos/2.jpg)


## The system in on the barrel
![The system is on a barrel](greenhouse-irrigation-system/photos/3.jpg)
![The system is on a barrel](greenhouse-irrigation-system/photos/4.jpg)


**Wiring**

---

### 📁 aquaflora / (Manual + TFT)

| Component | Pin |
|-----------|-----|
| TFT CS | 10 |
| TFT RST | 9 |
| TFT DC | 8 |
| TFT MOSI | 11 |
| TFT SCK | 13 |
| Relay (pump) | 3 |
| Button | 2 |
| Potentiometer | A0 |
| TFT VCC | 5V |
| Все GND | GND |

---

### 📁 bochka / (Auto tank)

| Component | Pin |
|-----------|-----|
| Relay (pump) | 3 |
| Water sensor | 2 |
| VCC | 5V |
| GND | GND |
---
Folder structure for repo:

```
greenhouse-irrigation-system/
├── aquaflora/           # Проект 1 (ручной полив с дисплеем)
│   ├── photos/
│   └── README.md
├── bochka/              # Проект 2 (автополив бочки)
│   ├── photos/
│   ├── README.md
│   └── bochka.ino
└── README.md            # Главный README
```

