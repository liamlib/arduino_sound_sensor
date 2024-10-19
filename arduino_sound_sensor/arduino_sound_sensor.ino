#include <Servo.h> 

int servoPin = 3; 
Servo Servo1; 

int sound_sensor = A0; 
int counter = 0;
bool lightOn = false;
unsigned long lastClapTime = 0;
const unsigned long clapTimeout = 2000; 
const unsigned long maxIntervalBetweenClaps = 1000; 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sound_sensor, INPUT);
  Serial.begin(9600); 
  Servo1.attach(servoPin); 
  Servo1.write(150); 
}

void loop() {
  int soundValue = analogRead(sound_sensor);
  unsigned long currentTime = millis();

  if (soundValue > 520) {
    if (currentTime - lastClapTime < maxIntervalBetweenClaps) {
      counter++;
    } else {
      counter = 1;  
    }

    lastClapTime = currentTime;
  
    delay(200);  
  }
  
  if (counter == 2) {
    if (currentTime - lastClapTime <= clapTimeout) {
      lightOn = !lightOn;
      digitalWrite(LED_BUILTIN, lightOn ? HIGH : LOW);
      Servo1.write(lightOn ? 110: 180);
      Serial.println(lightOn ? "Light ON" : "Light OFF");
    }
    counter = 0;  
  }

  if (currentTime - lastClapTime > clapTimeout) {
    counter = 0;
  }
}
