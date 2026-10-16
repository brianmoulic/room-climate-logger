#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Wokwi-GUEST";
const char* password = "";
// CHANGE THIS LINE to your live address + /api/readings
const char* serverUrl = "https://room-climate-logger.onrender.com/api/readings";

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
  HTTPClient http;
  http.setTimeout(60000);
  http.begin(client, serverUrl);
  http.addHeader("Content-Type", "application/json");

  String body = "{\"temperature\":" + String(t, 1) +
                ",\"humidity\":" + String(h, 1) +
                ",\"note\":\"from simulated sensor\"}";

  int code = http.POST(body);
  Serial.println("Sent: " + body);
  Serial.println("Response code: " + String(code));
  http.end();

  delay(30000);
}
