#include <Arduino.h>
#include <WiFi.h>
#include <pubsubclient.h>

const uint8_t LED_PIN = 3;

// WiFi credentials (move to a config file)
const char *ssid = "";
const char *password = "";

// MQTT broker (move to a config file)
const char *mqtt_server = "test.mosquitto.org";
const uint8_t mqtt_port = 1883;
//const char *mqtt_user = "chas";
//const char *mqtt_password = "chas1234";
//const char* mqtt_topic = "home/automation";

WiFiClient wifi;
PubSubClient mqtt(wifi);

void setup()
{
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    analogWrite(LED_PIN, 255);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected to ");
    Serial.println(ssid);

    if (wifi.connect("www.fldc.se", 80)) {
        Serial.println("Connection to test successful");
    } else {
        Serial.println("Connection to test failed");
        Serial.print("WiFi status: ");
        Serial.println(WiFi.status());
    }

    mqtt.setServer(mqtt_server, mqtt_port);
    while (!mqtt.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (mqtt.connect("ArduinoClient"))
        {
            Serial.println("connected");
            //mqtt.subscribe(mqtt_topic);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqtt.state());
            delay(2000);
        }
    }
}

void loop()
{
    if (!mqtt.connected())
    {
        while (!mqtt.connected())
        {
            Serial.print("Reconnecting to MQTT...");
            if (mqtt.connect("ArduinoClient"))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("failed, rc=");
                Serial.print(mqtt.state());
                delay(2000);
            }
        }
    }
    mqtt.loop();
}
