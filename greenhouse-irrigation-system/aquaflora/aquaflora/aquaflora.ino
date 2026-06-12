#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>


#define TFT_CS    10
#define TFT_RST   9
#define TFT_DC    8

#define RELAY1    5
#define RELAY2    6


#define BUTTON_PIN 2


#define POT_PIN    A0


#define BG_COLOR     ST77XX_BLACK
#define TEXT_COLOR   ST77XX_WHITE
#define ACCENT_COLOR ST77XX_CYAN
#define VALUE_COLOR  ST77XX_YELLOW
#define SUCCESS_COLOR ST77XX_GREEN
#define ERROR_COLOR  ST77XX_RED


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int selectedSeconds = 0;
bool lastButtonState = HIGH;
bool wateringActive = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
bool lastReading = HIGH;
int lastDisplaySeconds = -1;

void setup() {
  Serial.begin(9600);
  
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  
  tft.initR(INITR_GREENTAB);
  tft.fillScreen(BG_COLOR);
  tft.setTextWrap(false);
  
  // Анимация загрузки
  drawLoadingScreen();
  delay(2000);
  
  drawMainScreen();
  
  lastButtonState = digitalRead(BUTTON_PIN);
  lastReading = lastButtonState;
}

void drawLoadingScreen() {
  tft.fillScreen(BG_COLOR);
  

  tft.setTextColor(ACCENT_COLOR);
  tft.setTextSize(2);
  tft.setCursor(15, 30);
  tft.println("AQUA");
  tft.setCursor(25, 55);
  tft.println("FLORA");
  
  
  tft.drawRect(14, 90, 100, 10, ACCENT_COLOR);
  for(int i = 0; i < 100; i+=10) {
    tft.fillRect(15 + i, 91, 8, 8, ACCENT_COLOR);
    delay(50);
  }
  
  tft.setTextColor(TEXT_COLOR);
  tft.setTextSize(1);
  tft.setCursor(25, 115);
  tft.println("System Ready");
}

void drawMainScreen() {
  tft.fillScreen(BG_COLOR);
  
  tft.drawRect(2, 2, 124, 156, ACCENT_COLOR);
  tft.drawRect(4, 4, 120, 152, TEXT_COLOR);
  
  
  tft.fillRect(6, 6, 116, 20, ACCENT_COLOR);
  tft.setTextColor(BG_COLOR);
  tft.setTextSize(1);
  tft.setCursor(28, 12);
  tft.print("WATERING SYSTEM");
  
  
  tft.setTextColor(TEXT_COLOR);
  tft.setCursor(10, 40);
  tft.setTextSize(1);
  tft.print("Interval:");
  
  
  
  tft.setTextColor(TEXT_COLOR);
  tft.setCursor(10, 140);
  tft.print("PRESS BUTTON");

  lastDisplaySeconds = -1;
}

void drawPotentiometerIcon(int x, int y, int value) {
 
  const int maxWidth = 110;  
  
  
  int maxDisplayValue = 2048;  
  
 
  int displayValue = constrain(value, 1, maxDisplayValue);
  int barWidth = map(displayValue, 1, maxDisplayValue, 10, maxWidth);
  

  tft.fillRect(x, y, maxWidth, 8, ST77XX_BLACK);
  tft.fillRect(x, y, barWidth, 8, ACCENT_COLOR);
  
  
  tft.drawRect(x - 1, y - 1, maxWidth + 2, 10, ST77XX_WHITE);
}

void updateDisplay() {
  
  if (lastDisplaySeconds != selectedSeconds) {
  
    tft.fillRect(10, 55, 100, 50, BG_COLOR);
    

    tft.setTextColor(VALUE_COLOR);
    tft.setTextSize(2);
    tft.setCursor(20, 55);
    if(selectedSeconds < 10) tft.print(" ");
    tft.print(selectedSeconds);
    
    
    tft.setTextSize(1);
    tft.setCursor(75, 70);
    tft.print("sec");
    
    
    drawPotentiometerIcon(10, 105, selectedSeconds);
    
    tft.drawRect(8, 53, 100, 45, ACCENT_COLOR);
    
    lastDisplaySeconds = selectedSeconds;
  }
}

void startWatering() {
  wateringActive = true;
  
  tft.fillScreen(BG_COLOR);
  tft.drawRect(2, 2, 124, 156, SUCCESS_COLOR);
  
  // Заголовок
  tft.fillRect(6, 6, 116, 20, SUCCESS_COLOR);
  tft.setTextColor(BG_COLOR);
  tft.setTextSize(1);
  tft.setCursor(20, 12);
  tft.print("WATERING START");
  
  
  
  tft.setTextColor(TEXT_COLOR);
  tft.setTextSize(1);
  tft.setCursor(10, 100);
  tft.print("Duration:");
  tft.setCursor(75, 100);
  tft.setTextColor(ACCENT_COLOR);
  tft.setTextSize(2);
  tft.print(selectedSeconds);
  tft.print("s");
  

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  
  for (int sec = 0; sec < selectedSeconds; sec++) {
    
    int progress = map(sec, 0, selectedSeconds - 1, 0, 110);
    tft.fillRect(9, 125, progress, 8, SUCCESS_COLOR);
    tft.drawRect(8, 124, 112, 10, ACCENT_COLOR);
    
    
    tft.fillRect(40, 140, 60, 15, BG_COLOR);
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(1);
    tft.setCursor(40, 142);
    tft.print(sec + 1);
    tft.print("/");
    tft.print(selectedSeconds);
    
    delay(1000);
  }
  
 
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  
  
  tft.fillScreen(BG_COLOR);
  tft.drawRect(2, 2, 124, 156, ERROR_COLOR);
  
  tft.fillRect(6, 6, 116, 20, ERROR_COLOR);
  tft.setTextColor(BG_COLOR);
  tft.setCursor(20, 12);
  tft.print("COMPLETED!");
  
  delay(2000);
  
  drawMainScreen();
  wateringActive = false;
}

void loop() {
  if (!wateringActive) {
    
    int potValue = analogRead(POT_PIN);
    potValue -= potValue % 50;
    selectedSeconds = map(potValue, 0, 1023, 1, 2048);
    
    updateDisplay();
    
    
    bool currentReading = digitalRead(BUTTON_PIN);
    
    if (currentReading != lastReading) {
      lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (currentReading != lastButtonState && currentReading == LOW) {
        lastButtonState = currentReading;
        startWatering();
      } else {
        lastButtonState = currentReading;
      }
    }
    
    lastReading = currentReading;
    
  } else {
    delay(100);
  }
}