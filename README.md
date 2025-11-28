# Voice‑Operated Robot Car (Adafruit IO + Wi‑Fi)
Wi‑Fi connected robot car controlled by voice commands via Adafruit IO, using an ESP32, motor driver and smartphone interface to drive the car forward, backward, left, right or stop.

# Overview
This project implements a small robot car that receives motion commands from Adafruit IO MQTT feeds, which are typically driven by a smartphone voice assistant (Google assistant, Adafruit IO). The car’s microcontroller subscribes to dedicated MQTT topics for each command (Forward, Backward, Left, Right, Stand) and translates them into timed motor motions by driving four motor driver inputs. The design demonstrates cloud‑connected robotics, MQTT control and basic motion primitives on the Arduino platform.

# Features
- Connects to Wi‑Fi and Adafruit IO MQTT using `Adafruit_MQTT_Client` 
- Subscribes to five feeds: `Forward`, `backward`, `Left`, `Right`, `stand`, one per motion command 
- Maps each command payload to motor driver pins `D1–D4` for a 2‑wheel drive chassis
- Uses serial debug output to monitor subscription data and tune timings  
- Simple blocking based control suitable for introductory projects
  
# Hardware and components used
- ESP32 development board   
- Motor driver (L298)   
- 2 × DC motors 
- Chassis, wheels and 12 V battery pack 

# Getting Started
1. Adafruit IO setup
   - Create an Adafruit IO account and note your username and IO key  
   - Create five feeds named: `Forward`, `backward`, `Left`, `Right`, `stand` 
   - Configure your voice assistant to publish `0` or `1` to these feeds for the different commands
2. Configure the sketch  
   - Set `WLAN_SSID` and `WLAN_PASS` to your Wi‑Fi credentials 
   - Set `AIO_USERNAME` and `AIO_KEY` to your Adafruit IO username and key  
   - Adjust delays (4000, 6000, 7000 ms) if you want tighter or looser turns
3. Upload and test  
   - Open the sketch in Arduino IDE, select the correct board and port and upload  
   - Open the serial monitor at 115200 baud to see connection status and incoming commands  
   - From the Adafruit IO dashboard or your voice interface, send commands and verify the car responds accordingly

# Possible Extensions
- Replace blocking `delay()` calls with a non‑blocking state machine for smoother control and sensor integration  
- Add ultrasonic distance sensing and automatic stop or avoidance  
- Add RGB LEDs or a small display to indicate active command and connection status  
- Log command history and distances in Adafruit IO for later analysis

# How to Use This Repository
- /src/ – Arduino sketch for the robot car
- /circuit_diagrams/ – Schematics, wiring diagrams
- /docs/ – Photos and videos of the assembled prototype
