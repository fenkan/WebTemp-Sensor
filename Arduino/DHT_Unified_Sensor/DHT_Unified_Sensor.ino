#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define DHTPIN 4        // D2 på NodeMCU = GPIO4
#define DHTTYPE DHT11   // WPSE311 fungerar som DHT11

DHT dht(DHTPIN, DHTTYPE);

ESP8266WebServer server(80);  // Skapa webserver på port 80

// Wifi uppgifter
const char* ssid = "Tele2_5fd0df";
const char* password = "ttx392p7";

// Funktion som körs när någon går in på serverns IP
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


  // Anslut till WiFi
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

// Starta server
server.on("/", handleRoot);
server.begin();
Serial.println("🌐 Web server started");
}

void loop() {
  server.handleClient();
  delay(10);
}
