#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "config.h"

// =====================================
// OBJETOS
// =====================================

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// =====================================
// VARIÁVEIS
// =====================================

bool relayState = false;

unsigned long lastClapTime = 0;
unsigned long lastSensorPublish = 0;
unsigned long lastWifiAttempt = 0;
unsigned long lastMqttAttempt = 0;

// =====================================
// FUNÇÕES
// =====================================

void setRelay(bool state)
{
    relayState = state;

    digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);

    Serial.print("Relé: ");
    Serial.println(relayState ? "ON" : "OFF");

    if (mqttClient.connected())
    {
        mqttClient.publish(
            MQTT_TOPIC_RELAY_STATUS,
            relayState ? "ON" : "OFF",
            true
        );
    }
}

void toggleRelay()
{
    setRelay(!relayState);
}

// =====================================
// MQTT
// =====================================

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
    String message;

    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    message.trim();
    message.toUpperCase();

    Serial.print("Mensagem MQTT recebida: ");
    Serial.println(message);

    if (String(topic) == MQTT_TOPIC_RELAY_COMMAND)
    {
        if (message == "ON")
        {
            setRelay(true);
        }
        else if (message == "OFF")
        {
            setRelay(false);
        }
        else if (message == "TOGGLE")
        {
            toggleRelay();
        }
    }
}

void connectMQTT()
{
    if (mqttClient.connected())
    {
        return;
    }

    unsigned long now = millis();

    if (now - lastMqttAttempt < 5000)
    {
        return;
    }

    lastMqttAttempt = now;

    Serial.println("Tentando conectar ao MQTT...");

    String clientId = "ESP32-Lampada-" + String((uint32_t)ESP.getEfuseMac(), HEX);

    if (mqttClient.connect(
            clientId.c_str(),
            MQTT_USER,
            MQTT_PASSWORD,
            MQTT_TOPIC_ESP_STATUS,
            0,
            true,
            "OFFLINE"))
    {
        Serial.println("MQTT conectado!");

        mqttClient.subscribe(MQTT_TOPIC_RELAY_COMMAND);

        mqttClient.publish(
            MQTT_TOPIC_ESP_STATUS,
            "ONLINE",
            true
        );

        mqttClient.publish(
            MQTT_TOPIC_RELAY_STATUS,
            relayState ? "ON" : "OFF",
            true
        );
    }
    else
    {
        Serial.print("Falha MQTT. Estado: ");
        Serial.println(mqttClient.state());
    }
}

// =====================================
// WIFI
// =====================================

void connectWiFi()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    unsigned long now = millis();

    if (now - lastWifiAttempt < 5000)
    {
        return;
    }

    lastWifiAttempt = now;

    Serial.println("Tentando conectar ao Wi-Fi...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Conectando");
}

// =====================================
// DETECÇÃO DE PALMAS
// =====================================

void detectClap()
{
    int soundValue = analogRead(SOUND_SENSOR_PIN);

    unsigned long now = millis();

    if (
        soundValue >= CLAP_THRESHOLD &&
        now - lastClapTime >= CLAP_COOLDOWN
    )
    {
        Serial.print("PALMA DETECTADA! Valor: ");
        Serial.println(soundValue);

        toggleRelay();

        lastClapTime = now;
    }
}

// =====================================
// TELEMETRIA
// =====================================

void publishSensor()
{
    if (!mqttClient.connected())
    {
        return;
    }

    unsigned long now = millis();

    if (now - lastSensorPublish < 1000)
    {
        return;
    }

    lastSensorPublish = now;

    int soundValue = analogRead(SOUND_SENSOR_PIN);

    char value[16];

    snprintf(
        value,
        sizeof(value),
        "%d",
        soundValue
    );

    mqttClient.publish(
        MQTT_TOPIC_SOUND,
        value
    );
}

// =====================================
// SETUP
// =====================================

void setup()
{
    Serial.begin(115200);

    pinMode(RELAY_PIN, OUTPUT);

    digitalWrite(RELAY_PIN, LOW);

    analogReadResolution(12);

    WiFi.mode(WIFI_STA);

    mqttClient.setServer(
        MQTT_SERVER,
        MQTT_PORT
    );

    mqttClient.setCallback(mqttCallback);

    Serial.println();
    Serial.println("==============================");
    Serial.println(" ESP32 - LAMPADA POR PALMAS");
    Serial.println("==============================");

    connectWiFi();
}

// =====================================
// LOOP
// =====================================

void loop()
{
    // -------------------------------
    // Wi-Fi
    // -------------------------------

    if (WiFi.status() != WL_CONNECTED)
    {
        connectWiFi();
    }

    // -------------------------------
    // MQTT
    // -------------------------------

    if (WiFi.status() == WL_CONNECTED)
    {
        if (!mqttClient.connected())
        {
            connectMQTT();
        }
        else
        {
            mqttClient.loop();
        }
    }

    // -------------------------------
    // SENSOR
    // -------------------------------

    detectClap();

    // -------------------------------
    // TELEMETRIA
    // -------------------------------

    publishSensor();

    delay(10);
}