#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

// Definição dos pinos
#define PIR_PIN 12
#define TRIG_PIN 14
#define ECHO_PIN 13
#define LED_R 5
#define LED_G 18
#define LED_B 19
#define BUZZER_PIN 4
#define SERVO_PIN 15

// Configuração WiFi
const char* SSID = "CIT_Alunos";
const char* PASSWORD = "alunos@2024";

// Configuração MQTT
const char* MQTT_SERVER = "test.mosquitto.org";
const int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "monitoramento/alerta";

// Instâncias globais
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_MPU6050 mpu;
Servo servoMotor;

void setupWiFi() {
    Serial.print("Conectando ao WiFi...");
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(" Conectado!");
}

void reconnectMQTT() {
    while (!client.connected()) {
        Serial.print("Conectando ao MQTT...");
        if (client.connect("ESP32Monitor")) {
            Serial.println(" Conectado!");
            client.subscribe(MQTT_TOPIC);
        } else {
            Serial.print(" Falha, rc=");
            Serial.println(client.state());
            delay(5000);
        }
    }
}

float medirDistancia() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    return duration > 0 ? duration * 0.034 / 2 : -1;
}

void ativarAlerta(String mensagem) {
    Serial.println("🔴 ALERTA: " + mensagem);
    client.publish(MQTT_TOPIC, mensagem.c_str());
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    delay(2000);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_R, LOW);  
}

void lerGiroscopio() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    Serial.print("Giroscópio X: "); Serial.print(g.gyro.x);
    Serial.print(" | Y: "); Serial.print(g.gyro.y);
    Serial.print(" | Z: "); Serial.println(g.gyro.z);
    
    if (g.gyro.x < -0.10 || g.gyro.x > 0.10 || g.gyro.y < -0.10 || g.gyro.y > 0.10) {
    Serial.println("⚠️ Movimento detectado! Ativando servo...");
    servoMotor.write(90);
    delay(1000);
    servoMotor.write(0);
  }

}

void setup() {
    Serial.begin(115200);
    pinMode(PIR_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    servoMotor.attach(SERVO_PIN);
    setupWiFi();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    while (!mpu.begin()) {
        Serial.println("MPU6050 não encontrado! Tentando novamente...");
        delay(1000);
    }
    Serial.println("MPU6050 iniciado com sucesso!");
    digitalWrite(LED_G, HIGH);
}

void loop() {
    if (!client.connected()) reconnectMQTT();
    client.loop();
    
    if (digitalRead(PIR_PIN) == HIGH) ativarAlerta("Pessoa na cama!");
    
    float distancia = medirDistancia();
    if (distancia > 0 && distancia < 4444 && digitalRead(PIR_PIN) == LOW) {
        ativarAlerta("Usuário caiu da cama!");
    }
    
    lerGiroscopio();
    delay(1000);
}
