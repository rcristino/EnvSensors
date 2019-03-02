#include "DHT.h"
#include <ESP8266WiFi.h>

#define DHTPIN 4     // what pin we're connected tom in this case D2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define SLEEP 2000
#define MSG_SIZE 100

char* ssid = "YOUR_SSID";
char* password = "YOUR_WIRELESS_PASSWORD";

uint16_t port = 49000;
char * host = "192.168.XXX.XXX";

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600); 
  
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  int val = 0;
  char msg[100];
  WiFiClient client;

  if (!client.connect(host, port)) 
  {
    Serial.println("Connection to host failed");
    delay(SLEEP);
    return;
  }
  
  // Wait a few seconds between measurements.
  delay(SLEEP);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = h + dht.readHumidity();
  // Read temperature as Celsius
  float t = t + dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  sprintf(msg,"{\"hum\":\"%.1f\",\"temp\":\"%.1f\"}", h, t);

  Serial.println(msg); 
  client.print(msg);
  client.stop();

}
