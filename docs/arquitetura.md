# Arquitetura do Projeto

## Visão geral

O projeto possui quatro elementos principais:

1. ESP32;
2. Sensor de som MAX9814;
3. Relé;
4. Broker MQTT.

O ESP32 funciona como dispositivo IoT responsável por realizar a leitura do sensor, controlar o atuador e realizar a comunicação pela rede Wi-Fi.

## Fluxo por palma

```text
MAX9814
   |
   | sinal analógico
   v
GPIO 34
   |
   v
ESP32
   |
   | detecção de palma
   v
GPIO 26
   |
   v
Relé
   |
   v
Lâmpada