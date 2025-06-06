#include <WiFi.h>
 
//----------------------------------------------------------
 
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
 
//----------------------------------------------------------
// Definições e configurações
 
Adafruit_MPU6050 mpu;
 
// Pinos dos sensores
const int TEMP_SENSOR_PIN = 32; // Sensor de temperatura analógico
const int LDR_PIN = 33;         // Sensor de luminosidade (LDR)
 
// Wi-Fi
const char* SSID      = "Wokwi-GUEST";
const char* PASSWORD  = "";
 
// MQTT Broker 
const char* BROKER_MQTT  = "broker.hivemq.com";
const int   BROKER_PORT  = 1883;
const char* mqttUser     = "gs2025";
const char* mqttPassword = "q1w2e3r4";
 
// Tópico MQTT
#define TOPICO_PUBLISH  "sensor/dados"
 
//----------------------------------------------------------
// Variáveis globais
 
const char* moduleID  = "RM553415";
 
WiFiClient espClient;
PubSubClient MQTT(espClient);
JsonDocument doc;  // Documento JSON dinâmico
char buffer[256];  // Buffer para o JSON serializado
 
//----------------------------------------------------------
// Conexão Wi-Fi
 
void initWiFi() {
 
   
 
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Conectando ao Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}
 
void reconectaWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconectando Wi-Fi...");
        initWiFi();
    }
}
 
//----------------------------------------------------------
// Conexão MQTT
 
void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    while (!MQTT.connected()) {
        Serial.println("Conectando ao Broker MQTT...");
        if (MQTT.connect(moduleID, mqttUser, mqttPassword)) {
            Serial.println("Conectado ao Broker!");
        } else {
            Serial.print("Falha na conexão. Estado: ");
            Serial.println(MQTT.state());
            delay(2000);
        }
    }
}
 
void verificaConexoesWiFiEMQTT() {
    reconectaWiFi();
    if (!MQTT.connected()) {
        initMQTT();
    }
    MQTT.loop();
}
 
//----------------------------------------------------------
// Envio e feedback
 
void enviaEstadoOutputMQTT() {
    MQTT.publish(TOPICO_PUBLISH, buffer);
    Serial.println("Mensagem publicada com sucesso!");
}
 
 
 
//----------------------------------------------------------
// Setup inicial
 
void setup() {
 
    if (!mpu.begin()) {
    Serial.println("Erro ao iniciar MPU6050!");
    while (1);
    }    
    Serial.begin(115200);    
     
    initWiFi();    
    initMQTT();
}
 
//----------------------------------------------------------
// Loop principal
 
void loop() {
    // Verifica e mantém conexões ativas com Wi-Fi e MQTT
    verificaConexoesWiFiEMQTT();
   
    // Temperatura analógica (exemplo aproximado)
    int analogTemp = analogRead(TEMP_SENSOR_PIN);
    float temperatura = (analogTemp / 4095.0) * 330.0; // Conversão para °C aprox.
 
    // Luminosidade (LDR)
    int luminosidade = analogRead(LDR_PIN);
 
    // Acelerômetro MPU6050
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
 
 
    // Limpa o documento JSON para nova utilização
    doc.clear();
 
    // Dados:  
    doc["ID"] = moduleID;
    doc["Temperatura"] = temperatura;
    doc["Luminosidade"] = luminosidade;
    doc["Aceleração X"] = a.acceleration.x;
    doc["Aceleração Y"] = a.acceleration.y;
    doc["Aceleração Z"] = a.acceleration.z;  
 
    // Serializa JSON para string
    serializeJson(doc, buffer);
 
    // Exibe no monitor serial
    Serial.println(buffer);
 
    // Envia via MQTT
    enviaEstadoOutputMQTT();  
 
    // Intervalo de envio
    delay(10000);
}
 