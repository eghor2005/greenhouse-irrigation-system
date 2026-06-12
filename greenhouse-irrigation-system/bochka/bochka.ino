// Пин реле оставляем тот же (3)
const int RELAY_PIN = 3;
// Определяем пин, к которому подключен желтый провод датчика
const int SENSOR_PIN = 2;

// Переменные для таймеров
unsigned long waterLowTimer = 0;      // Таймер для отсутствия воды
unsigned long waterHighTimer = 0;     // Таймер для наличия воды
bool waterWasLow = false;              // Флаг, что вода была ниже датчика
bool relayState = false;               // Текущее состояние реле (HIGH = включено)

// Настройки задержек (в миллисекундах)
const unsigned long DELAY_BEFORE_ON = 30UL * 60UL * 1000UL;  // 30 минут до включения
const unsigned long DELAY_BEFORE_OFF = 15UL * 1000UL;        // 15 секунд до выключения

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  
  // Включаем подтягивающий резистор
  digitalWrite(SENSOR_PIN, HIGH);
  
  digitalWrite(RELAY_PIN, LOW);  // Реле выключено
  Serial.begin(9600);
}

void loop() {
  int isWaterDetected = digitalRead(SENSOR_PIN);
  unsigned long currentMillis = millis();
  
  // Логика для ситуации, когда воды нет (датчик на HIGH)
  if (isWaterDetected == HIGH) {
    Serial.println("Water level: NOT DETECTED (HIGH signal)");
    
    if (!waterWasLow) {
      // Вода только что ушла - запускаем таймер на включение
      waterLowTimer = currentMillis;
      waterWasLow = true;
      Serial.print("Water dropped below sensor. Will turn ON relay after ");
      Serial.print(DELAY_BEFORE_ON / 60000);
      Serial.println(" minutes if water stays low");
    }
    
    // Проверяем, прошло ли 30 минут
    if (waterWasLow && (currentMillis - waterLowTimer >= DELAY_BEFORE_ON)) {
      if (!relayState) {
        digitalWrite(RELAY_PIN, HIGH);
        relayState = true;
        Serial.println("Relay TURNED ON - 30 minutes passed without water");
      }
    }
    
    // Сбрасываем таймер выключения, если вода вернулась
    waterHighTimer = 0;
  }
  
  // Логика для ситуации, когда вода есть (датчик на LOW)
  else {
    Serial.println("Water level: DETECTED (LOW signal)");
    
    // Если реле было включено (качаем воду) и вода вернулась
    if (relayState) {
      if (waterHighTimer == 0) {
        // Вода только что появилась - запускаем таймер на выключение
        waterHighTimer = currentMillis;
        Serial.print("Water detected. Will turn OFF relay after ");
        Serial.print(DELAY_BEFORE_OFF / 1000);
        Serial.println(" seconds if water stays high");
      }
      
      // Проверяем, прошла ли 1 минута
      if (currentMillis - waterHighTimer >= DELAY_BEFORE_OFF) {
        digitalWrite(RELAY_PIN, LOW);
        relayState = false;
        waterWasLow = false;
        waterHighTimer = 0;
        Serial.println("Relay TURNED OFF - Water level remained high for 1 minute");
      }
    } 
    // Если вода есть, но реле выключено - сбрасываем флаг waterWasLow
    else {
      waterWasLow = false;
      waterLowTimer = 0;
    }
  }
  
  // Вывод текущего состояния реле
  if (relayState) {
    Serial.println("Relay is ON (pumping water)");
  } else {
    Serial.println("Relay is OFF");
  }
  
  delay(500);
}