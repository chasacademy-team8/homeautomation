#ifndef CONFIG_H
#define CONFIG_H

// Pin configuration
#define LED_PIN_1 3
#define LED_PIN_2 6
#define SMOKE_SENSOR_PIN_D 4
#define SMOKE_SENSOR_PIN_A A1
#define BUZZER_PIN 5
#define PHOTORESISTOR_PIN A0

// display configuration
#define LCD_RS 13
#define LCD_EN 12
#define LCD_D4 11
#define LCD_D5 10
#define LCD_D6 9
#define LCD_D7 8

// LED configuration
#define TURN_ON_HOUR 8
#define TURN_OFF_HOUR 24

#define LIGHT_OFF 0
#define LIGHT_LOW 64
#define LIGHT_MEDIUM 128
#define LIGHT_HIGH 255

// smoke sensor configuration
#define SMOKE_THRESHOLD 500

// wifi settings
#define WIFI_ATTEMPTS 5

#endif
