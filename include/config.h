#ifndef CONFIG_H
#define CONFIG_H

// ===============================
// PINOS
// ===============================

#define SOUND_SENSOR_PIN 34
#define RELAY_PIN 26

// ===============================
// DETECÇÃO DE PALMAS
// ===============================

// Ajustar experimentalmente durante os testes.
#define CLAP_THRESHOLD 2500

// Tempo mínimo entre duas detecções de palma.
#define CLAP_COOLDOWN 800

// ===============================
// WIFI
// ===============================

#define WIFI_SSID "SUA_REDE_WIFI"
#define WIFI_PASSWORD "SUA_SENHA_WIFI"

// ===============================
// MQTT
// ===============================

#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883

#define MQTT_USER ""
#define MQTT_PASSWORD ""

// Trocar pelo identificador real da equipe.
#define MQTT_BASE "grupoX"

// ===============================
// TOPICOS MQTT
// ===============================

#define MQTT_TOPIC_SOUND MQTT_BASE "/sensor/som"
#define MQTT_TOPIC_RELAY_COMMAND MQTT_BASE "/comando/rele"
#define MQTT_TOPIC_RELAY_STATUS MQTT_BASE "/status/rele"
#define MQTT_TOPIC_ESP_STATUS MQTT_BASE "/status/esp32"

#endif