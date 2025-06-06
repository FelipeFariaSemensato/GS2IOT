# 🌍 Plataforma IoT para Monitoramento de Sensores com ESP32 e MQTT

Este projeto realiza a leitura de sensores com um ESP32 e publica os dados via MQTT. Os dados são visualizados em tempo real utilizando o **Node-RED Dashboard**.

## 📦 Tecnologias Utilizadas

- ESP32 (Wokwi ou físico)
- Sensores: temperatura analógica, LDR, MPU6050
- MQTT (Broker HiveMQ ou servidor local)
- Node-RED Dashboard
- Arduino IDE ou VS Code com PlatformIO
- Bibliotecas: ArduinoJson, PubSubClient, Adafruit_MPU6050

---

## ⚙️ Funcionalidades

- Leitura da temperatura ambiente (sensor analógico)
- Medição da luminosidade com LDR
- Leitura de aceleração nos eixos X, Y e Z com MPU6050
- Envio periódico dos dados em formato JSON via MQTT
- Visualização dos dados em tempo real no Node-RED Dashboard

---

## 🔌 Montagem dos Sensores

| Sensor       | Pino ESP32 |
|--------------|------------|
| Temperatura  | GPIO 32    |
| LDR          | GPIO 33    |
| MPU6050 (I2C)| GPIO 21 (SDA), GPIO 22 (SCL) |

---

## 📡 Conexão Wi-Fi e MQTT

- **SSID Wi-Fi**: `Wokwi-GUEST`
- **Senha**: *(vazio)*
- **Broker MQTT**: `broker.hivemq.com`
- **Porta**: `1883`
- **Tópico**: `projeto/sensores`
- **Cliente MQTT**: `esp32-cliente`

---

## 🧩 Fluxo Node-RED

1. Acesse: [https://nodered.org/](https://nodered.org/)
2. No menu superior direito, clique em **Import > Clipboard**
3. Cole o JSON do fluxo fornecido na pasta `/node-red` deste repositório
4. Configure o nó MQTT-IN:

5. Clique em **Deploy**
6. Abra o Dashboard do Node-RED (ícone no canto superior direito) para ver os dados em tempo real

---

## 🌐 Configuração do Broker MQTT (HiveMQ)

- **Broker**: `broker.hivemq.com`
- **Porta**: `1883`
- **Tópico**: `sensor/dados`
- **Cliente**: `esp32-cliente`

---

## 🧪 Testes

### ✅ Como Testar no Wokwi

1. Acesse [https://wokwi.com](https://wokwi.com)
2. Faça login e abra o projeto de simulação (`.ino`)
3. Monte os sensores conforme a tabela acima
4. Clique em **Start Simulation**
5. Acompanhe o monitor serial para ver o JSON sendo enviado
6. No Node-RED, visualize os dados chegando e sendo exibidos em tempo real

---

### 🛠️ Problemas Comuns

| Erro | Solução |
|------|---------|
| Temperatura -127 ou 0.00 | Verifique as conexões do sensor e se está correto o cálculo |
| `missing broker configuration` no Node-RED | Configure corretamente o nó MQTT-IN com o broker e porta |
| Dashboard não mostra nada | Confirme se há nós `ui_*` no fluxo e se o deploy foi feito |

---

## 📁 Estrutura do Projeto

```bash
📦 Projeto
 ┣ 📂 node-red
 ┃ ┗ 📄 flows.json
 ┣ 📄 sensores_mqtt.ino
 ┣ 📄 README.md
