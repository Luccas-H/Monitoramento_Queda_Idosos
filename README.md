# 🏥 Monitor de Q IoT para Idosos  

Este projeto é um **sistema de monitoramento de segurança baseado em IoT** utilizando um **ESP32**. Ele foi desenvolvido para detectar movimentos, prevenir quedas e alertar cuidadores em tempo real.  

## 🚀 Funcionalidades  
- 📡 **Detecção de Movimento**: Utiliza um **sensor PIR** para identificar movimentações inesperadas.  
- 📏 **Medição de Distância**: O **sensor ultrassônico HC-SR04** detecta tentativas de sair da cama/cadeira.  
- 🔄 **Detecção de Quedas**: O **giroscópio MPU6050** monitora a inclinação do corpo para detectar quedas.  
- 🔊 **Alertas e Notificações**:  
  - 🔴 **LED RGB** muda de cor conforme o nível de alerta.  
  - 📢 **Buzzer** emite som para avisar sobre situações de risco.  
  - ⚙️ **Servo Motor** ativa barreiras de proteção automaticamente.  
- 📲 **Conectividade**:  
  - 🌐 Comunicação via **MQTT** para enviar alertas em tempo real.  
  - 📱 Integração com um **aplicativo móvel** para notificações remotas.  

## 🛠 Componentes Utilizados  
### **Sensores**  
- 🔵 **PIR** → Detecta presença/movimento.  
- 📏 **HC-SR04** → Mede distância para identificar tentativas de saída da cama.  
- 🔄 **MPU6050** → Detecta inclinação para verificar quedas.  

### **Atuadores**  
- 🔊 **Buzzer** → Emite alerta sonoro em caso de emergência.  
- 🌈 **LED RGB** → Indica status do sistema.  
- ⚙️ **Servo Motor** → Ativa barreiras de segurança.  

## 🔌 Esquema de Conexão  
| Componente | Pino ESP32 |
|------------|------------|
| PIR Sensor | GPIO 12 |
| HC-SR04 Trig | GPIO 14 |
| HC-SR04 Echo | GPIO 13 |
| MPU6050 (SDA) | GPIO 21 |
| MPU6050 (SCL) | GPIO 22 |
| LED RGB (R) | GPIO 5 |
| LED RGB (G) | GPIO 18 |
| LED RGB (B) | GPIO 19 |
| Buzzer | GPIO 4 |
| Servo Motor | GPIO 15 |

## 📦 Instalação  
1. **Baixe e instale as bibliotecas necessárias** no Arduino IDE:  
   - `WiFi.h` (para conexão com a internet)  
   - `PubSubClient.h` (para MQTT)  
   - `Wire.h`, `Adafruit_MPU6050.h`, `Adafruit_Sensor.h` (para MPU6050)  
   - `Servo.h` (para controle do servomotor)  

2. **Configure sua rede WiFi e servidor MQTT** no código:  
   ```cpp
   const char* SSID = "Seu_WiFi";
   const char* PASSWORD = "Sua_Senha";
   const char* MQTT_SERVER = "broker.hivemq.com";

3. **Compile e envie o código para o ESP32.**
4. **Abra o Monitor Serial** para verificar os dados do sensor.

## 📲 Como Usar
1️⃣ **Conecte o ESP32** à alimentação elétrica.  
2️⃣ O sistema iniciará automaticamente e começará a monitorar os sensores.  
3️⃣ Se houver detecção de movimento, queda ou tentativa de sair da cama/cadeira:  
   - 🔴 O **LED RGB** indicará o nível de alerta.  
   - 📢 O **buzzer** será ativado para emitir um alerta sonoro.  
   - ⚙️ O **servo motor** pode acionar uma barreira de proteção.  
   - 🌐 O **ESP32 enviará um alerta via MQTT** para o aplicativo móvel.  
4️⃣ O usuário poderá visualizar os alertas em tempo real no aplicativo móvel conectado.  

