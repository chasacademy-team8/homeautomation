# Home Automation System

## Overview

This project is a home automation system designed to control various devices such as lights, buzzers, and sensors.
It uses an Arduino microcontroller to interface with these devices.

## Features

* **Smoke Detection**: Detects smoke and triggers an alarm with a buzzer and LED.
* **Light Control**: Automatically adjusts light brightness based on ambient light levels.
* **Time-Based Light Control**: Turns lights on and off based on the time of day.
* **Status Display**: Displays system status and messages on an LCD screen.
* **WiFi Connectivity**: Connects to a WiFi network for time synchronization using an NTP server.

## Getting Started

### **Prerequisites:**

* Visual Studio Code or equivalent IDE
* PlatformIO extension
* Required libraries:
  * LiquidCrystal
  * NTPClient

### Installation

#### From Release

1. Download the latest firmware release from the [Releases](https://github.com/orgs/chasacademy-team8/releases) page.
2. Connect your Arduino to your computer.
3. Use the Arduino IDE or PlatformIO to upload the firmware to your Arduino.

#### From Source

1. Clone the repository:

    ```sh
    git clone https://github.com/orgs/chasacademy-team8/homeautomation.git
    ```

2. Open the project in Visual Studio Code.
3. Ensure you have the PlatformIO extension installed.
4. Open the PlatformIO Home tab in Visual Studio Code.
5. Connect your Arduino to your computer.
6. Build and upload the firmware using the PlatformIO extension:
    1. Click on the PlatformIO icon in the sidebar.
    2. Select "Build" to compile the project.
    3. Select "Upload" to upload the firmware to your Arduino.

## Latest Release

You can download the latest release from the [Releases](https://github.com/orgs/chasacademy-team8/releases) page.

## Documentation

* [Project Idea](docs/idea.md)
* [SRS](docs/SRS.md)
* [Roadmap](https://github.com/orgs/chasacademy-team8/projects/3/views/7?sortedBy%5Bdirection%5D=asc&sortedBy%5BcolumnId%5D=174871397)
* [Milestones](https://github.com/chasacademy-team8/homeautomation/milestones)
* [Circuit](https://www.tinkercad.com/things/2BIRUlRgJSR-home-automation-system?sharecode=CB0rbs8jnQo0wepwYxnte0_Uei58wCmuA0ZicQ_sXoc)

![Circuit breadboard](docs/Circuit_breadboard.png)
![Circuit diagram](docs/Circuit_diagram.png)

## License

This project is licensed under the MIT License.
