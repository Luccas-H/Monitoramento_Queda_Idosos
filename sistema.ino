#include <Wire.h>
#include "MPU6050.h"
#include <ESP32Servo.h>

#define RED_LED 5     // GPIO pin for RED LED
#define GREEN_LED 18  // GPIO pin for GREEN LED
#define BLUE_LED 19   // GPIO pin for BLUE LED
#define Servo_PIN 15
#define Trig_PIN 35
#define Echo_PIN 33
#define Potenciometro_PIN 12
#define Buzzer_PIN 13
MPU6050 mpu;
Servo myServo;

// Threshold values (adjust based on testing)
const float MOVEMENT_THRESHOLD = 1.1;  // Moderate movement threshold
const float EXTREME_THRESHOLD = 1.5;   // Extreme movement threshold (edge detection)
const int DISTANCIA_MIN = 30;


long getDistance()
{
  digitalWrite(Trig_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_PIN, LOW);
  long duration = pulseIn(Echo_PIN, HIGH, 30000);
  Serial.println(duration);
  return duration > 0 ? duration * 0.034 / 2 : -1;
  
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA = GPIO 21, SCL = GPIO 22
  mpu.initialize();

  myServo.attach(Servo_PIN);
  myServo.write(0);

  pinMode(Potenciometro_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  pinMode(Trig_PIN, OUTPUT);
  pinMode(Echo_PIN, INPUT);
  pinMode(Buzzer_PIN, OUTPUT);

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1)
      ;
  }
  Serial.println("MPU6050 connected!");
}

void setLED(int r, int g, int b) {
  digitalWrite(RED_LED, r);
  digitalWrite(GREEN_LED, g);
  digitalWrite(BLUE_LED, b);
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  int distance = getDistance();
  // Convert raw values to approximate G-force
  
  int potValue = analogRead(Potenciometro_PIN);
  int simulatedDistance = map(potValue,0,4095,2,50);
  Serial.println(simulatedDistance);
  float accelMagnitude = sqrt(sq(ax / 16384.0) + sq(ay / 16384.0) + sq(az / 16384.0));

  Serial.print("Acceleration Magnitude: ");
  Serial.println(accelMagnitude);
  Serial.println(distance);
  if(simulatedDistance > 30)
  {
      digitalWrite(Buzzer_PIN, HIGH);
      delay(2000);
      digitalWrite(Buzzer_PIN, LOW);
  }
  // Determine LED state
  if (accelMagnitude < 1.1 ) {
    setLED(1,0, 1);  // Green (Still) 1 0 1 
    delay(1500);
  } else if (accelMagnitude > 2 ) {
    setLED(1, 1, 0);  // Red (Extreme movement)011
    delay(1500);
    myServo.write(90);
  } else {
    setLED(1, 0,0);  // Yellow (Moderate movement)
    delay(1500);
  }

  delay(500);  // Adjust delay as needed
}
