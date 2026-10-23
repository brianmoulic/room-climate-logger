#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* host = "room-climate-logger.onrender.com";
const char* path = "/api/readings";

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password, 6);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Sensor read failed");
    delay(2000);
    return;
  }

  WiFiClientSecure client;
  client.setInsecure();

  Serial.println("Connecting to server...");
  if (!client.connect(host, 443)) {
    Serial.println("Connection to server failed");
    delay(30000);
    return;
  }

    String body = "{\"temperature\":" + String(t, 1) +
                ",\"humidity\":" + String(h, 1) +
                ",\"note\":\"from simulated sensor\"}";

  client.println("POST " + String(path) + " HTTP/1.1");
  client.println("Host: " + String(host));
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println("Content-Length: " + String(body.length()));
  client.println();
  client.print(body);

  Serial.println("Sent: " + body);

  client.setTimeout(30000);
  unsigned long start = millis();
  while (client.connected() && !client.available() && millis() - start < 40000) {
    delay(100);
  }
  Serial.println("Waited ms: " + String(millis() - start));

  String status = client.readStringUntil('\n');
  Serial.println("Server replied: [" + status + "]");
  client.stop();

  delay(30000);
}
