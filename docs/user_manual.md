# Home Automation System - User Manual

## Hardware Requirements

- Arduino R4 WiFi microcontroller
- Smoke sensor
- Buzzer
- LEDs
- Photoresistor
- LCD display
- WiFi module

---

## Software Requirements

- Visual Studio Code with PlatformIO extension
- Required libraries:
  - LiquidCrystal
  - NTPClient

---

## Setup Instructions

### Hardware Setup

1. Connect the smoke sensor to the Arduino's analog and digital pins as specified in `config.h`.
2. Connect the buzzer to the pin defined as `BUZZER_PIN`.
3. Connect the photoresistor to the pin defined as `PHOTORESISTOR_PIN`.
4. Connect the LEDs to the pins defined as `LED_PIN_1`.
5. Connect the LCD display to the pins defined in the `config.h` file.

### Software Setup

1. Clone the repository:

    ```sh
    git clone https://github.com/orgs/chasacademy-team8/homeautomation.git
    ```

2. Open the project in Visual Studio Code.
3. Install the PlatformIO extension.
4. Build and upload the firmware to your Arduino:
    - Click the PlatformIO icon in the sidebar.
    - Select "Build" to compile the project.
    - Select "Upload" to upload the firmware.

---

## Usage Instructions

1. Power on the Arduino.
2. The system will automatically connect to the WiFi network using the credentials in `wifi_settings.h`.
3. The LCD will display the current time and system status.
4. The system will:
   - Adjust light brightness based on ambient light.
   - Turn lights on/off based on the time of day.
   - Trigger an alarm if smoke is detected.

---

## Troubleshooting

### Smoke Alarm Not Triggering

- Ensure the smoke sensor is properly connected and calibrated.
- Check the `SMOKE_SENSOR_PIN_A` connection.

### Lights Not Adjusting

- Verify the photoresistor is connected to the correct pin.
- Check the ambient light thresholds in `config.h`.

### WiFi Not Connecting

- Ensure the WiFi credentials in `wifi_settings.h` are correct.
