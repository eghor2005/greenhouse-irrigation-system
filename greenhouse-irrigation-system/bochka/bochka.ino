
const int RELAY_PIN = 3;

const int SENSOR_PIN = 2;


unsigned long waterLowTimer = 0;      
unsigned long waterHighTimer = 0;  
bool waterWasLow = false;          
bool relayState = false;          


const unsigned long DELAY_BEFORE_ON = 30UL * 60UL * 1000UL;  
const unsigned long DELAY_BEFORE_OFF = 15UL * 1000UL;      

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  
  digitalWrite(SENSOR_PIN, HIGH);
  
  digitalWrite(RELAY_PIN, LOW); 
  Serial.begin(9600);
}

void loop() {
  int isWaterDetected = digitalRead(SENSOR_PIN);
  unsigned long currentMillis = millis();
  
  
  if (isWaterDetected == HIGH) {
    Serial.println("Water level: NOT DETECTED (HIGH signal)");
    
    if (!waterWasLow) {
      
      waterLowTimer = currentMillis;
      waterWasLow = true;
      Serial.print("Water dropped below sensor. Will turn ON relay after ");
      Serial.print(DELAY_BEFORE_ON / 60000);
      Serial.println(" minutes if water stays low");
    }
    
    
    if (waterWasLow && (currentMillis - waterLowTimer >= DELAY_BEFORE_ON)) {
      if (!relayState) {
        digitalWrite(RELAY_PIN, HIGH);
        relayState = true;
        Serial.println("Relay TURNED ON - 30 minutes passed without water");
      }
    }
   
    waterHighTimer = 0;
  }
  
  
  else {
    Serial.println("Water level: DETECTED (LOW signal)");
    
   
    if (relayState) {
      if (waterHighTimer == 0) {

        waterHighTimer = currentMillis;
        Serial.print("Water detected. Will turn OFF relay after ");
        Serial.print(DELAY_BEFORE_OFF / 1000);
        Serial.println(" seconds if water stays high");
      }
      

      if (currentMillis - waterHighTimer >= DELAY_BEFORE_OFF) {
        digitalWrite(RELAY_PIN, LOW);
        relayState = false;
        waterWasLow = false;
        waterHighTimer = 0;
        Serial.println("Relay TURNED OFF - Water level remained high for 1 minute");
      }
    } 
    
    else {
      waterWasLow = false;
      waterLowTimer = 0;
    }
  }
  

  if (relayState) {
    Serial.println("Relay is ON (pumping water)");
  } else {
    Serial.println("Relay is OFF");
  }
  
  delay(500);
}
