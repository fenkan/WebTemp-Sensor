# WebTemp-Sensor

A simple ESP8266-based temperature and humidity sensor with a web interface.

This project reads temperature and humidity data from a DHT sensor (or compatible sensor) and displays the values on a web page hosted by the ESP8266.  
You can monitor your room or environment remotely via any web browser on the same network.

## Features

- Reads temperature and humidity from the sensor
- Hosts a web server on ESP8266
- Displays real-time sensor data on a web page
- Easy to deploy on any ESP8266 module
- See Max and Min temperature through the current session (values reset when the app stops or ESP restarts)

## Hardware

- ESP8266 module (e.g., NodeMCU)
- Temperature & humidity sensor (e.g., DHT11 or DHT22)
- Jumper wires and breadboard (optional)

## Usage

1. Connect the sensor to the ESP8266 following the wiring diagram.
2. Update your Wi-Fi credentials in the `WebTemp-Sensor.ino` file:
   const char* wifi_ssid = "YOUR_WIFI_SSID";
   const char* wifi_pass = "YOUR_WIFI_PASSWORD";
