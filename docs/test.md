**Software Requirements Specification (SRS)**

**1. Introduction**

1.1 Purpose  
This document specifies the requirements for the Home Automation System, which aims to automate lighting and fire detection using the Arduino platform.

1.2 Scope  
The system will provide automated control over home lighting based on ambient light, time, and motion detection. It will also include a fire alarm system that responds to smoke detection. The system is intended for homeowners looking to implement basic home automation features. It will be developed using Arduino and various sensors.

1.3 Definitions, Acronyms, and Abbreviations  
- **Arduino** – A microcontroller platform used to control the system.  
- **PIR Sensor** – Passive Infrared Sensor used for motion detection.  
- **RTC** – Real-Time Clock module for tracking time.  
- **Fire Sensor** – A sensor used to detect smoke or fire.  

1.4 References  
[Links or references to related documents]

1.5 Overview  
This document describes functional and non-functional requirements, design constraints, and other aspects of the system.

---

**2. Overall Description**

2.1 Product Perspective  
The system is a standalone home automation solution designed to enhance convenience and safety. It will interact with sensors and output devices such as LEDs, buzzers, and actuators to automate lighting and fire alarm functionalities.

2.2 Product Functions  
The system will include the following functions:  
- **Light Control**: Turns lights on/off based on motion detection.  
- **Light Dimmer**: Adjusts light brightness based on ambient light.  
- **Light Controller**: Controls lights based on the time of day.  
- **Fire Alarm**: Triggers an alarm when smoke is detected.  
- **Fire Alarm Light Control**: Turns lights on/off when smoke is detected.  

2.3 User Characteristics  
The target audience consists of homeowners.. Users should be able to install and configure the system with minimal technical expertise.

2.4 Constraints  
- The system will rely on the availability of power.
- Hardware components such as sensors must be properly calibrated for accurate detection.

---

**3. Specific Requirements**

3.1 Functional Requirements  
- The system shall turn lights on when motion is detected.
- The system shall adjust light brightness based on ambient light conditions.
- The system shall control lights based on time of day.
- The system shall trigger an alarm when smoke is detected.
- The system shall control lights in case of a fire alarm.

3.2 Non-Functional Requirements  
- The system should respond to sensor inputs within 1 second.
- The system should be user-friendly and easy to configure.

3.3 External Interface Requirements  
- **User Interface**: Simple status updates on a LCD freom the system.
- **Hardware Interfaces**: Arduino microcontroller, PIR sensor, fire sensor, RTC module, LED lights, and buzzer.

3.4 System Features  
- Real-time light control based on environmental conditions.
- Automated alarm system for fire detection.
- Modular design allowing additional sensors and features.

---

**4. Appendices**

Any appendices, sample data, or diagrams supporting the document.

---


