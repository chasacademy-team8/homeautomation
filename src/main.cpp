#include <Arduino.h>
#include <WiFiS3.h>
#include <PubSubClient.h>
#include "config.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const char* mqtt_server = MQTT_SERVER;
const int mqtt_port = MQTT_PORT;

WiFiClient wifi;
PubSubClient mqtt(wifi);

void ledState(uint8_t ledPin, uint8_t state)
{
    if (state == 1)
    {
        //Serial.println("LED ON"); // debug
        digitalWrite(ledPin, 1);
    }
    else
    {
        //Serial.println("LED OFF"); // debug
        digitalWrite(ledPin, 0);
    }
}

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    uint8_t state = payload[0] == '1' ? HIGH : LOW;

    if (strcmp(topic, MQTT_TOPIC_LIGHT_1) == 0)
    {
        ledState(LED_PIN, state);
    }
}

void mqttReconnect()
{
    uint8_t timeout = 0;

    while (!mqtt.connected() && timeout < 5)
    {
        Serial.print("Attempting MQTT connection...");
        if (mqtt.connect("ArduinoClient"))
        {
            Serial.println("connected");
            mqtt.subscribe(MQTT_TOPIC_LIGHT_1);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqtt.state());
            delay(2000);
        }
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    // Initialize WiFi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.print("Connected to ");
    Serial.println(ssid);

    // Initialize MQTT
    mqtt.setServer(mqtt_server, mqtt_port);
    mqtt.setCallback(mqttCallback);

    mqttReconnect();

    if(mqtt.connected())
    {
        // Set the initial states on broker if the device is connected
        mqtt.publish(MQTT_TOPIC_LIGHT_1, 0);
    }
}

void loop()
{
    if (!mqtt.connected())
    {
        mqttReconnect();
    }
    mqtt.loop();
}
