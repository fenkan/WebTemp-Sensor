#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define DHTPIN 4        // D2 on NodeMCU = GPIO4
#define DHTTYPE DHT11   // WPSE311 works like DHT11

DHT dht(DHTPIN, DHTTYPE);

ESP8266WebServer server(80);  // Create a web server on port 80

// Wifi uppgifter
const char* ssid = ""; // Add you wifi ssid
const char* password = ""; // Add your wifi password

//  Function that runs when someone accesses the server IP
void handleRoot(){
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    server.send(500, "text/plain", "Failed to read from DHT sensor!");
    return;
  }

String message = "{";
message += "\"temperature\": " + String(temp, 1) + ",";
message += "\"humidity\": " + String(hum, 1);
message += "}";

server.send(200, "application/json; charset=utf-8", message);

}

void setup() {
  Serial.begin(115200);
  dht.begin();


  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}


Serial.println("");
Serial.println("✅ WiFi connected!");
Serial.print("IP adress: ");
Serial.println(WiFi.localIP());

// Start the server
server.on("/", handleRoot);
server.begin();
Serial.println("🌐 Web server started");
}

void loop() {
  server.handleClient();
  delay(10);
}
